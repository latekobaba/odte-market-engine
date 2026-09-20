#include <iostream>
#include <vector>
#include <chrono>

#include <map>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "OptionTrade.h"
#include "MarketDataEngine.h"
#include "ETFTradeParser.h"
#include "../include/ETFBarAggregator.h"
#include "OptionTradeParser.h"
#include "OptionBarAggregator.h"
#include "MarketBarAggregator.h"
#include "TBBOTradeParser.h"
#include "TBBOBarAggregator.h"


int main() {

    // ---------------------------------------------------------
    // Synthetic OptionTrade examples
    // ---------------------------------------------------------

    OptionTrade trade(
        "2023-01-03 09:35:00.000",
        "SPY",
        "2023-01-03",
        550.0,
        'C',
        2.35,
        100,
        2.30,
        2.40,
        0.25,
        0.52,
        0.08,
        551.20,
        551.30
    );


    // Creates a container capable of holding many OptionTrade objects.
    std::vector<OptionTrade> trades;

    trades.push_back(trade);


    trades.emplace_back(
        "2023-01-03 09:35:30.000",
        "SPY",
        "2023-01-03",
        552.0,
        'C',
        1.85,
        50,
        1.80,
        1.90,
        0.24,
        0.48,
        0.07,
        551.25,
        551.35
    );


    trades.emplace_back(
        "2023-01-03 09:36:00.000",
        "SPY",
        "2023-01-03",
        548.0,
        'P',
        1.40,
        75,
        1.35,
        1.45,
        0.26,
        -0.42,
        0.07,
        551.15,
        551.25
    );


    // ---------------------------------------------------------
    // MarketDataEngine
    // ---------------------------------------------------------

    MarketDataEngine engine;

    engine.reserve(3);

    for (const OptionTrade& t : trades) {
        engine.addTrade(t);
    }


    std::cout << "Engine Trade Count: "
              << engine.getTradeCount() << '\n';

    std::cout << "Engine Total Volume: "
              << engine.getTotalVolume() << '\n';

    std::cout << "Engine Total Notional: "
              << engine.getTotalNotional() << '\n';

    std::cout << "Engine Call Volume: "
              << engine.getCallVolume() << '\n';

    std::cout << "Engine Put Volume: "
              << engine.getPutVolume() << '\n';

    std::cout << "Engine VWAP: "
              << engine.getVWAP() << '\n';

    std::cout << "Engine Put/Call Ratio: "
              << engine.getPutCallRatio() << '\n';


#ifdef __linux__
    std::cout << "Platform: Linux\n";
#elif _WIN32
    std::cout << "Platform: Windows\n";
#endif


    // ---------------------------------------------------------
    // Print synthetic option trades
    // ---------------------------------------------------------

    for (const OptionTrade& t : trades) {

        std::cout << "\nTrade\n";

        std::cout << "Symbol: "
                  << t.getSymbol() << '\n';

        std::cout << "Strike: "
                  << t.getStrike() << '\n';

        std::cout << "Option Type: "
                  << t.getOptionType() << '\n';

        std::cout << "Price: "
                  << t.getPrice() << '\n';

        std::cout << "Size: "
                  << t.getSize() << '\n';

        std::cout << "Moneyness: "
                  << t.getMoneyness() << '\n';

        std::cout << "Notional: "
                  << t.getNotional() << '\n';
    }


    // =========================================================
    // REAL CBOE 0DTE OPTION DATA
    // =========================================================

    // ---------------------------------------------------------
    // Parse real CBOE option trades
    // ---------------------------------------------------------

    OptionTradeParser optionParser;


    // Start CBOE parser benchmark
    auto cboeParseStart =
        std::chrono::high_resolution_clock::now();


    std::vector<OptionTrade> cboeTrades =
        optionParser.parseFile(
            "/home/lateef/cpp_projects/project1-odte-market-engine/data/cboe_spy_qqq_0dte.csv"
        );


    // Stop CBOE parser benchmark
    auto cboeParseEnd =
        std::chrono::high_resolution_clock::now();


    std::chrono::duration<double> cboeParseTime =
        cboeParseEnd - cboeParseStart;


    std::cout << "\nParsed CBOE Option Trades: "
              << cboeTrades.size()
              << std::endl;


    std::cout << "CBOE Parse Time: "
              << cboeParseTime.count()
              << " seconds\n";


    if (cboeParseTime.count() > 0.0) {

        double cboeParseThroughput =
            cboeTrades.size() /
            cboeParseTime.count();

        std::cout << "CBOE Parse Throughput: "
                  << cboeParseThroughput
                  << " trades/second\n";
    }


    // ---------------------------------------------------------
    // Print first CBOE option trade
    // ---------------------------------------------------------

    if (!cboeTrades.empty()) {

        const OptionTrade& firstCboeTrade =
            cboeTrades.front();


        std::cout << "\nFirst CBOE Option Trade:\n";


        std::cout << "Timestamp: "
                  << firstCboeTrade.getTimestamp()
                  << '\n';

        std::cout << "Symbol: "
                  << firstCboeTrade.getSymbol()
                  << '\n';

        std::cout << "Expiration: "
                  << firstCboeTrade.getExpiration()
                  << '\n';

        std::cout << "Strike: "
                  << firstCboeTrade.getStrike()
                  << '\n';

        std::cout << "Option Type: "
                  << firstCboeTrade.getOptionType()
                  << '\n';

        std::cout << "Price: "
                  << firstCboeTrade.getPrice()
                  << '\n';

        std::cout << "Size: "
                  << firstCboeTrade.getSize()
                  << '\n';

        std::cout << "Best Bid: "
                  << firstCboeTrade.getBestBid()
                  << '\n';

        std::cout << "Best Ask: "
                  << firstCboeTrade.getBestAsk()
                  << '\n';

        std::cout << "IV: "
                  << firstCboeTrade.getImpliedVolatility()
                  << '\n';

        std::cout << "Delta: "
                  << firstCboeTrade.getDelta()
                  << '\n';

        std::cout << "Gamma: "
                  << firstCboeTrade.getGamma()
                  << '\n';

        std::cout << "Underlying Bid: "
                  << firstCboeTrade.getUnderlyingBid()
                  << '\n';

        std::cout << "Underlying Ask: "
                  << firstCboeTrade.getUnderlyingAsk()
                  << '\n';

        std::cout << "Underlying Mid: "
                  << firstCboeTrade.getUnderlyingPrice()
                  << '\n';

        std::cout << "Moneyness: "
                  << firstCboeTrade.getMoneyness()
                  << '\n';

        std::cout << "Notional: "
                  << firstCboeTrade.getNotional()
                  << '\n';
    }


    // ---------------------------------------------------------
    // Aggregate CBOE 0DTE option trades into 5-minute bars
    // ---------------------------------------------------------

    // ---------------------------------------------------------
    // Aggregate CBOE 0DTE option trades into 5-minute bars
    // ---------------------------------------------------------

    OptionBarAggregator optionBarAggregator;

    auto optionAggregationStart =
        std::chrono::high_resolution_clock::now();

    std::vector<OptionBar> optionBars =
        optionBarAggregator.aggregate(cboeTrades);

    auto optionAggregationEnd =
        std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> optionAggregationTime =
        optionAggregationEnd - optionAggregationStart;

    std::cout << "\n5-Minute 0DTE Option Bars: "
              << optionBars.size()
              << '\n';

    std::cout << "CBOE Option Aggregation Time: "
              << optionAggregationTime.count()
              << " seconds\n";

    if (optionAggregationTime.count() > 0.0) {

        double optionAggregationThroughput =
            cboeTrades.size() /
            optionAggregationTime.count();

        std::cout << "CBOE Option Aggregation Throughput: "
                  << optionAggregationThroughput
                  << " trades/second\n";
    }


    std::cout << "\n5-Minute 0DTE Option Bars: "
              << optionBars.size()
              << std::endl;


    // ---------------------------------------------------------
    // Print first 0DTE option bar
    // ---------------------------------------------------------

    if (!optionBars.empty()) {

        const OptionBar& firstOptionBar =
            optionBars.front();


        std::cout
            << "\nFirst 5-Minute 0DTE Option Bar:\n";


        std::cout << "Start Timestamp: "
                  << firstOptionBar.getStartTimestamp()
                  << '\n';

        std::cout << "Symbol: "
                  << firstOptionBar.getSymbol()
                  << '\n';

        std::cout << "Trade Count: "
                  << firstOptionBar.getTradeCount()
                  << '\n';

        std::cout << "Total Volume: "
                  << firstOptionBar.getTotalVolume()
                  << '\n';

        std::cout << "Total Notional: "
                  << firstOptionBar.getTotalNotional()
                  << '\n';

        std::cout << "Call Volume: "
                  << firstOptionBar.getCallVolume()
                  << '\n';

        std::cout << "Put Volume: "
                  << firstOptionBar.getPutVolume()
                  << '\n';

        std::cout << "VWAP: "
                  << firstOptionBar.getVWAP()
                  << '\n';

        std::cout << "Average Spread: "
                  << firstOptionBar.getAverageSpread()
                  << '\n';

        std::cout << "Average IV: "
                  << firstOptionBar.getAverageIV()
                  << '\n';

        std::cout << "Average Delta: "
                  << firstOptionBar.getAverageDelta()
                  << '\n';

        std::cout << "Average Gamma: "
                  << firstOptionBar.getAverageGamma()
                  << '\n';

        std::cout << "Put/Call Ratio: "
                  << firstOptionBar.getPutCallRatio()
                  << '\n';

        std::cout << "Average ATM Distance: "
                  << firstOptionBar.getAverageATMDistance()
                  << '\n';
    }


    // =========================================================
    // SYNTHETIC ETF BENCHMARK PIPELINE
    // =========================================================

    // ---------------------------------------------------------
    // Parse Databento ETF trades
    // ---------------------------------------------------------

    ETFTradeParser parser;


    auto parseStart =
        std::chrono::high_resolution_clock::now();


    std::vector<ETFTrade> etfTrades =
        parser.parseFile(
            "data/etf_trades_large.csv"
        );


    auto parseEnd =
        std::chrono::high_resolution_clock::now();


    std::chrono::duration<double> parseTime =
        parseEnd - parseStart;


    std::cout << "\nParsed ETF Trades: "
              << etfTrades.size()
              << '\n';


    std::cout << "ETF Parse Time: "
              << parseTime.count()
              << " seconds\n";


    double parseThroughput =
        etfTrades.size() /
        parseTime.count();


    std::cout << "ETF Parse Throughput: "
              << parseThroughput
              << " trades/second\n";


    /*
    for (const ETFTrade& trade : etfTrades) {
        trade.print();
        std::cout << '\n';
    }
    */


    // ---------------------------------------------------------
    // Aggregate ETF trades into 5-minute bars
    // ---------------------------------------------------------

    ETFBarAggregator aggregator;


    auto aggregationStart =
        std::chrono::high_resolution_clock::now();


    std::vector<ETFBar> bars =
        aggregator.aggregate(etfTrades);


    auto aggregationEnd =
        std::chrono::high_resolution_clock::now();


    std::chrono::duration<double> aggregationTime =
        aggregationEnd - aggregationStart;


    std::cout << "\n5-Minute ETF Bars: "
              << bars.size()
              << "\n\n";


    std::cout << "ETF Aggregation Time: "
              << aggregationTime.count()
              << " seconds\n\n";


    // ---------------------------------------------------------
    // Print ETF bars
    // ---------------------------------------------------------

    for (const ETFBar& bar : bars) {

        bar.print();

        std::cout << '\n';
    }


    // ---------------------------------------------------------
    // ETF 5-minute returns
    // ---------------------------------------------------------

    std::cout
        << "\nETF 5-Minute Return Series:\n";


    for (std::size_t i = 1;
         i < bars.size();
         ++i) {

        double etfReturn =
            bars[i].getReturn(
                bars[i - 1]
            );


        std::cout << "Interval "
                  << i
                  << " Return: "
                  << etfReturn
                  << '\n';
    }


    // ---------------------------------------------------------
    // Integrate ETF and 0DTE option 5-minute bars
    // ---------------------------------------------------------

    MarketBarAggregator marketBarAggregator;


    std::vector<MarketBar> marketBars =
        marketBarAggregator.aggregate(
            bars,
            optionBars
        );


    std::cout << "\nMatched Market Bar Timestamps:\n";


    for (const MarketBar& marketBar : marketBars) {

        std::cout
            << "ETF: "
            << marketBar.getETFBar().getStartTimestamp()
            << " | "
            << marketBar.getETFBar().getSymbol()
            << "  <->  Option: "
            << marketBar.getOptionBar().getStartTimestamp()
            << " | "
            << marketBar.getOptionBar().getSymbol()
            << '\n';
    }


    std::cout
        << "\nIntegrated ETF + 0DTE Market Bars: "
        << marketBars.size()
        << '\n';


    // ---------------------------------------------------------
    // Print first integrated market bar
    // ---------------------------------------------------------

    if (!marketBars.empty()) {

        const MarketBar& firstMarketBar =
            marketBars.front();


        const ETFBar& integratedETFBar =
            firstMarketBar.getETFBar();


        const OptionBar& integratedOptionBar =
            firstMarketBar.getOptionBar();


        std::cout
            << "\nFirst Integrated Market Bar:\n";


        std::cout << "ETF Timestamp: "
                  << integratedETFBar.getStartTimestamp()
                  << '\n';


        std::cout << "ETF Symbol: "
                  << integratedETFBar.getSymbol()
                  << '\n';


        std::cout << "ETF VWAP: "
                  << integratedETFBar.getVWAP()
                  << '\n';


        std::cout << "Option Timestamp: "
                  << integratedOptionBar.getStartTimestamp()
                  << '\n';


        std::cout << "Option Symbol: "
                  << integratedOptionBar.getSymbol()
                  << '\n';


        std::cout << "0DTE Volume: "
                  << integratedOptionBar.getTotalVolume()
                  << '\n';


        std::cout << "Option VWAP: "
                  << integratedOptionBar.getVWAP()
                  << '\n';


        std::cout << "Put/Call Ratio: "
                  << integratedOptionBar.getPutCallRatio()
                  << '\n';


        std::cout << "Average ATM Distance: "
                  << integratedOptionBar.getAverageATMDistance()
                  << '\n';
    }


    // =========================================================
    // REAL DATABENTO SPY TBBO PIPELINE
    // =========================================================

    // ---------------------------------------------------------
    // Parse real Databento SPY TBBO trades
    // ---------------------------------------------------------

    std::cout << "\n=== REAL SPY TBBO TEST ===\n";

    TBBOTradeParser tbboParser;


    auto tbboParseStart =
        std::chrono::high_resolution_clock::now();


    std::vector<TBBOTrade> tbboTrades =
        tbboParser.parseCSV(
            "data/spy_tbbo_2023-01-03.csv",
            "SPY"
        );


    auto tbboParseEnd =
        std::chrono::high_resolution_clock::now();


    std::chrono::duration<double> tbboParseTime =
        tbboParseEnd - tbboParseStart;


    std::cout << "Parsed TBBO Trades: "
              << tbboTrades.size()
              << '\n';


    std::cout << "TBBO Parse Time: "
              << tbboParseTime.count()
              << " seconds\n";


    if (tbboParseTime.count() > 0.0) {

        double tbboThroughput =
            tbboTrades.size() /
            tbboParseTime.count();

        std::cout << "TBBO Parse Throughput: "
                  << tbboThroughput
                  << " trades/second\n";
    }


    // ---------------------------------------------------------
    // Print first real TBBO trade
    // ---------------------------------------------------------

    if (!tbboTrades.empty()) {

        const TBBOTrade& firstTBBOTrade =
            tbboTrades.front();


        std::cout << "\nFirst TBBO Trade:\n";


        std::cout << "Timestamp: "
                  << firstTBBOTrade.getTimestamp()
                  << '\n';

        std::cout << "Symbol: "
                  << firstTBBOTrade.getSymbol()
                  << '\n';

        std::cout << "Price: "
                  << firstTBBOTrade.getPrice()
                  << '\n';

        std::cout << "Size: "
                  << firstTBBOTrade.getSize()
                  << '\n';

        std::cout << "Side: "
                  << firstTBBOTrade.getSide()
                  << '\n';

        std::cout << "Bid: "
                  << firstTBBOTrade.getBidPrice()
                  << '\n';

        std::cout << "Ask: "
                  << firstTBBOTrade.getAskPrice()
                  << '\n';

        std::cout << "Bid Size: "
                  << firstTBBOTrade.getBidSize()
                  << '\n';

        std::cout << "Ask Size: "
                  << firstTBBOTrade.getAskSize()
                  << '\n';

        std::cout << "Mid: "
                  << firstTBBOTrade.getMidPrice()
                  << '\n';

        std::cout << "Quoted Spread: "
                  << firstTBBOTrade.getQuotedSpread()
                  << '\n';

        std::cout << "Effective Spread: "
                  << firstTBBOTrade.getEffectiveSpread()
                  << '\n';

        std::cout << "Notional: "
                  << firstTBBOTrade.getNotional()
                  << '\n';
    }


    // ---------------------------------------------------------
    // Aggregate real SPY TBBO trades into 5-minute bars
    // ---------------------------------------------------------

    std::cout << "\n=== REAL SPY TBBO 5-MINUTE BARS ===\n";

    TBBOBarAggregator tbboBarAggregator;


    auto tbboAggregationStart =
        std::chrono::high_resolution_clock::now();


    std::vector<TBBOBar> tbboBars =
        tbboBarAggregator.aggregate(tbboTrades);


    auto tbboAggregationEnd =
        std::chrono::high_resolution_clock::now();


    std::chrono::duration<double> tbboAggregationTime =
        tbboAggregationEnd - tbboAggregationStart;


    std::cout << "5-Minute TBBO Bars: "
              << tbboBars.size()
              << '\n';


    std::cout << "TBBO Aggregation Time: "
              << tbboAggregationTime.count()
              << " seconds\n";


    // ---------------------------------------------------------
    // Print first real 5-minute TBBO bar
    // ---------------------------------------------------------

    if (!tbboBars.empty()) {

        const TBBOBar& firstTBBOBar =
            tbboBars.front();

        std::cout << "\nFirst 5-Minute TBBO Bar:\n";

        firstTBBOBar.print();
    }


    // =========================================================
    // REAL DATABENTO TBBO + CBOE 0DTE INTEGRATION TEST
    // =========================================================

    std::cout
        << "\n=== REAL TBBO + CBOE INTEGRATION TEST ===\n";


    // ---------------------------------------------------------
    // Index SPY OptionBars by their timestamp string.
    //
    // Example:
    //     2023-01-03 09:30
    // ---------------------------------------------------------

    std::map<std::string, const OptionBar*>
        spyOptionBarMap;


    for (const OptionBar& optionBar : optionBars) {

        if (optionBar.getSymbol() == "SPY") {

            spyOptionBarMap[
                optionBar.getStartTimestamp()
            ] = &optionBar;
        }
    }


    // ---------------------------------------------------------
    // Match each real SPY TBBO bar with its corresponding
    // real SPY CBOE 0DTE OptionBar.
    // ---------------------------------------------------------

    auto integrationStart =
    std::chrono::high_resolution_clock::now();

    int matchedRealBars = 0;

    const TBBOBar* firstMatchedTBBOBar = nullptr;
    const OptionBar* firstMatchedOptionBar = nullptr;


    for (const TBBOBar& tbboBar : tbboBars) {

        // Convert Unix nanoseconds -> seconds
        std::time_t seconds =
            static_cast<std::time_t>(
                tbboBar.getStartTimestamp()
                / 1000000000LL
            );


        // January 2023:
        // Eastern Standard Time = UTC - 5 hours
        seconds -= 5 * 60 * 60;


        std::tm easternTime =
            *std::gmtime(&seconds);


        std::ostringstream timestampStream;


        timestampStream
            << std::put_time(
                &easternTime,
                "%Y-%m-%d %H:%M"
            );


        std::string tbboTimestamp =
            timestampStream.str();


        auto match =
            spyOptionBarMap.find(
                tbboTimestamp
            );


        if (match != spyOptionBarMap.end()) {

            matchedRealBars++;


            // Save the first match so we can inspect it
            if (firstMatchedTBBOBar == nullptr) {

                firstMatchedTBBOBar =
                    &tbboBar;

                firstMatchedOptionBar =
                    match->second;
            }
        }
    }


    auto integrationEnd =
    std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> integrationTime =
        integrationEnd - integrationStart;

    // ---------------------------------------------------------
    // Report integration result
    // ---------------------------------------------------------

    std::cout
        << "Matched Real SPY Bars: "
        << matchedRealBars
        << '\n';

    std::cout
        << "Real Market Integration Time: "
        << integrationTime.count()
        << " seconds\n";

    // ---------------------------------------------------------
    // Print first matched real market interval
    // ---------------------------------------------------------

    if (firstMatchedTBBOBar != nullptr &&
        firstMatchedOptionBar != nullptr) {

        std::cout
            << "\nFirst Matched Real Market Interval:\n";


        std::cout
            << "TBBO Timestamp: "
            << firstMatchedTBBOBar
                   ->getStartTimestamp()
            << '\n';


        std::cout
            << "Symbol: "
            << firstMatchedTBBOBar
                   ->getSymbol()
            << '\n';


        // ----- Databento TBBO side -----

        std::cout
            << "TBBO VWAP: "
            << firstMatchedTBBOBar
                   ->getVWAP()
            << '\n';


        std::cout
            << "Average Quoted Spread: "
            << firstMatchedTBBOBar
                   ->getAverageQuotedSpread()
            << '\n';


        std::cout
            << "Average Effective Spread: "
            << firstMatchedTBBOBar
                   ->getAverageEffectiveSpread()
            << '\n';


        std::cout
            << "Average Bid Size: "
            << firstMatchedTBBOBar
                   ->getAverageBidSize()
            << '\n';


        std::cout
            << "Average Ask Size: "
            << firstMatchedTBBOBar
                   ->getAverageAskSize()
            << '\n';


        std::cout
            << "Average Order Imbalance: "
            << firstMatchedTBBOBar
                   ->getAverageOrderImbalance()
            << '\n';


        // ----- CBOE 0DTE option side -----

        std::cout
            << "Option Timestamp: "
            << firstMatchedOptionBar
                   ->getStartTimestamp()
            << '\n';


        std::cout
            << "0DTE Volume: "
            << firstMatchedOptionBar
                   ->getTotalVolume()
            << '\n';


        std::cout
            << "Option VWAP: "
            << firstMatchedOptionBar
                   ->getVWAP()
            << '\n';


        std::cout
            << "Put/Call Ratio: "
            << firstMatchedOptionBar
                   ->getPutCallRatio()
            << '\n';


        std::cout
            << "Average ATM Distance: "
            << firstMatchedOptionBar
                   ->getAverageATMDistance()
            << '\n';
    }


    return 0;
}