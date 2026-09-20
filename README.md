# High-Performance 0DTE Market-Data Engine

This project is a C++20 market-data engine for processing high-frequency ETF and 0DTE options data.

I built it mainly to work with the kind of large market datasets I use in my quantitative finance research. The focus here is not on building another trading strategy. The focus is the engineering underneath it: ingest the data, process it efficiently, construct synchronized market bars, calculate useful market statistics, and do all these fast enough for large datasets.

The engine currently handles CBOE option trades and Databento ETF/TBBO data.

## What the Engine Does

At a high level, the pipeline does the following:

```text
Raw Market Data
      |
      v
   Parsers
      |
      v
Trade / TBBO Objects
      |
      v
5-Minute Aggregators
      |
      v
Market Statistics
      |
      v
ETF + 0DTE Integration
```

The current implementation includes:

- CBOE options trade ingestion
- identification and filtering of 0DTE contracts
- Databento ETF trade ingestion
- Databento TBBO ingestion
- 5-minute option aggregation
- 5-minute ETF/TBBO aggregation
- synchronization of ETF and option-market intervals
- automated C++ tests with CTest
- Release-mode benchmarking
- Linux `perf` profiling

For the option side, the engine calculates statistics such as volume, call/put volume, VWAP, quoted spread, implied volatility, delta, gamma, put/call ratio and distance from ATM.

For the ETF/TBBO side, it calculates VWAP, quoted spread, effective spread, bid/ask depth and order imbalance.

## Why I Built It

A lot of quantitative research starts in Python, including mine. That is very useful for research and econometrics, but I wanted to go further into the systems side of quantitative finance.

So I built this engine in C++ from the ground up.

One objective was to understand what actually happens when the same market-data operations are implemented with more attention to memory allocation, data structures, copies, parsing cost and algorithmic overhead.

I also did not want this to become a C++ rewrite just for the sake of saying "I used C++". Each major optimization was benchmarked, and some implementations were rejected because they were actually slower.

## Market-Data Pipeline

### CBOE Options

```text
CBOE CSV
    |
    v
OptionTradeParser
    |
    v
0DTE OptionTrade objects
    |
    v
OptionBarAggregator
    |
    v
5-minute OptionBar objects
```

The parser reads the CBOE trade records and retains contracts where the market date equals the expiration date.

The resulting 0DTE trades are then aggregated into 5-minute intervals.

### Databento TBBO

```text
Databento TBBO
      |
      v
TBBOTradeParser
      |
      v
TBBOTrade objects
      |
      v
TBBOBarAggregator
      |
      v
5-minute TBBOBar objects
```

The TBBO bars contain both trade and prevailing quote information, which makes it possible to calculate microstructure measures such as quoted spread, effective spread, displayed depth and order imbalance.

### Cross-Market Integration

The final integration step matches the ETF/TBBO intervals with the corresponding CBOE 0DTE option intervals.

For the SPY validation session used here:

```text
SPY TBBO bars:          78
Matched option bars:    78
Match rate:             78 / 78
```

This gives a synchronized intraday representation of the ETF and its 0DTE option market.

## Real-Market Validation

I validated the engine using real SPY market data for January 3, 2023.

The validation run included:

```text
CBOE option trades:       521,418
SPY TBBO observations:     91,614
0DTE option bars:              162
SPY TBBO bars:                  78
Matched SPY intervals:       78/78
```

The 162 option bars include the option symbols processed by the option pipeline, while the integration test specifically matches SPY intervals.

One example of a matched interval:

```text
Timestamp:                  2023-01-03 09:30
SPY TBBO VWAP:              384.288
Average Quoted Spread:      0.021543
Average Effective Spread:   0.0202832
Average Bid Size:           206.807
Average Ask Size:           265.614
Average Order Imbalance:   -0.0339794

0DTE Volume:                108311
Option VWAP:                1.02348
Put/Call Ratio:             0.882393
Average ATM Distance:       0.00720474
```

For me, getting the 78/78 alignment was an important correctness check because the two datasets come from different market-data pipelines and use different timestamp representations.

## Performance

All final performance numbers below are from a CMake **Release** build running under Linux/WSL2.

### CBOE Parsing

The engine processed:

```text
521,418 option trades
```

Repeated Release runs produced approximately:

```text
Run 1: 482K trades/sec
Run 2: 597K trades/sec
Run 3: 597K trades/sec
```

The two later warm-cache runs were approximately **597K trades/sec**.

### 0DTE Aggregation

The optimized 5-minute option aggregation ran at approximately:

```text
13 million trades/sec
```

Representative Release results:

```text
Aggregation time:        ~0.040 sec
Aggregation throughput:  ~13.0M trades/sec
5-minute option bars:    162
```

These figures will naturally depend on hardware, compiler, filesystem and cache state. They are measurements from my development environment, not claimed as universal performance numbers.

## Optimization Work

This part of the project was particularly useful.

The first working `OptionBarAggregator` was correct, but it was doing more work than necessary.

The original development-build performance was approximately:

```text
418K trades/sec
```

I then optimized it in stages.

### 1. Direct Accumulation

Instead of putting copies of `OptionTrade` objects into buckets and making another pass later, the aggregator accumulates the required statistics directly into the bucket state.

That moved throughput to roughly:

```text
652K trades/sec
```

### 2. Timestamp Processing

The earlier implementation was doing relatively expensive timestamp conversion inside the hot path.

I removed the repeated `stoi` / stream-based timestamp construction and used the timestamp characters directly when creating the 5-minute bucket.

Result:

```text
~887K trades/sec
```

### 3. Hash-Based Bucketing

The ordered-map bucket structure was replaced with `std::unordered_map`.

After aggregation, I sort the finished bars so the external result is still deterministic.

That brought the development-build throughput to approximately:

```text
1.7M trades/sec
```

In the final Release build, the same aggregation pipeline runs around:

```text
13M trades/sec
```

So this was not just changing code until it looked more sophisticated. Each change was measured.

## Some Optimizations Did Not Work

I think this is worth documenting because not every "optimization" is actually an optimization.

Profiling showed that parsing remained one of the main bottlenecks. I therefore tested alternative CSV parsing approaches.

One implementation using a fixed array of parsed string fields performed much worse:

```text
~112K trades/sec
```

Another implementation used `std::string_view`, but still required temporary string creation for some numeric conversions. It achieved only about:

```text
~275K trades/sec
```

Both were slower than the existing parser, so I removed them.

The current parser was retained because it was the better measured implementation, not because it looked cleaner on paper.

## Profiling

I used Linux `perf` to profile the executable.

A representative profile showed the option `parseFile` path as a major part of total execution cost. Numeric conversion through `std::stod` and CSV field extraction with `std::getline` were also visible costs.

This is useful because it tells me where future optimization work should be concentrated instead of guessing.

The profiler output is included here:

```text
results/perf_report.txt
```

## Testing

The project currently has five automated tests:

```text
OptionTradeTest
OptionBarAggregatorTest
TBBOTradeTest
TBBOBarAggregatorTest
MarketIntegrationTest
```

Running:

```bash
ctest --test-dir cmake-build-release-wsl --output-on-failure
```

produces:

```text
100% tests passed, 0 tests failed out of 5
```

The tests cover the basic trade representations, aggregation logic and the market-integration layer.

## Building the Project

The project requires:

- C++20
- CMake
- a C++20-compatible compiler
- Linux or WSL2

Configure:

```bash
cmake -S . -B cmake-build-release -DCMAKE_BUILD_TYPE=Release
```

Build:

```bash
cmake --build cmake-build-release -j
```

Run:

```bash
./cmake-build-release/odte_market_engine
```

Run the tests:

```bash
ctest --test-dir cmake-build-release --output-on-failure
```

## Repository Structure

```text
.
├── include/
│   ├── MarketBar.h
│   ├── MarketBarAggregator.h
│   ├── OptionBar.h
│   ├── OptionBarAggregator.h
│   ├── OptionTrade.h
│   ├── OptionTradeParser.h
│   ├── TBBOBar.h
│   ├── TBBOBarAggregator.h
│   ├── TBBOTrade.h
│   └── TBBOTradeParser.h
│
├── src/
│   ├── main.cpp
│   ├── MarketBar.cpp
│   ├── MarketBarAggregator.cpp
│   ├── OptionBar.cpp
│   ├── OptionBarAggregator.cpp
│   ├── OptionTrade.cpp
│   ├── OptionTradeParser.cpp
│   ├── TBBOBar.cpp
│   ├── TBBOBarAggregator.cpp
│   ├── TBBOTrade.cpp
│   └── TBBOTradeParser.cpp
│
├── tests/
│   ├── test_option_trade.cpp
│   ├── test_option_bar_aggregator.cpp
│   ├── test_tbbo_trade.cpp
│   ├── test_tbbo_bar_aggregator.cpp
│   └── test_market_integration.cpp
│
├── results/
│   └── perf_report.txt
│
├── CMakeLists.txt
└── README.md
```

There is also an ETF trade pipeline used during ingestion and aggregation benchmarking.

## Data

The project was developed using licensed market data from CBOE and Databento.

The raw market-data files are **not included in this repository**. These datasets can be large, and more importantly, their redistribution is subject to the applicable vendor licences.

The repository therefore contains the C++ engine, tests, profiling output and documentation, but not the underlying CBOE/Databento datasets.

This means cloning the repository does not automatically give access to the same proprietary input data used for my validation runs.

## Where This Fits

This is Project 1 of a three-project quantitative C++ portfolio I am building:

```text
Project 1
High-Performance 0DTE Market-Data Engine
              |
              v
Project 2
0DTE Options Analytics / Microstructure Engine
              |
              v
Project 3
0DTE Signal & Backtesting Engine
```

Project 1 is deliberately about the market-data infrastructure.

The next layers will use this foundation for more quantitative analysis, market microstructure work and eventually signal/backtesting research.

For this first project, I wanted to get the data engineering right first before putting another model on top of it.