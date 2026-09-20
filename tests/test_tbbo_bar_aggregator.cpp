#include "TBBOTrade.h"
#include "TBBOBar.h"
#include "TBBOBarAggregator.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

int main() {

    std::vector<TBBOTrade> trades;

    // Three SPY trades in the same 09:30 five-minute interval.

    trades.emplace_back(
        1672756210000000000LL,
        "SPY",
        100.00,
        10,
        'B',
        99.90,
        100.10,
        200,
        100
    );

    trades.emplace_back(
        1672756260000000000LL,
        "SPY",
        101.00,
        20,
        'A',
        100.80,
        101.20,
        100,
        300
    );

    trades.emplace_back(
        1672756340000000000LL,
        "SPY",
        102.00,
        30,
        'B',
        101.90,
        102.10,
        400,
        200
    );

    TBBOBarAggregator aggregator;

    std::vector<TBBOBar> bars =
        aggregator.aggregate(trades);

    // All three observations belong to one 5-minute bucket.
    assert(bars.size() == 1);

    const TBBOBar& bar = bars[0];

    assert(bar.getSymbol() == "SPY");
    assert(bar.getTradeCount() == 3);

    // Total volume = 10 + 20 + 30 = 60
    assert(bar.getTotalVolume() == 60);

    // Dollar volume:
    // 100*10 + 101*20 + 102*30
    // = 6080
    assert(
        std::abs(bar.getDollarVolume() - 6080.0) < 1e-9
    );

    // VWAP = 6080 / 60
    double expectedVWAP = 6080.0 / 60.0;

    assert(
        std::abs(bar.getVWAP() - expectedVWAP) < 1e-9
    );

    // Quoted spreads:
    // 0.20, 0.40, 0.20
    // average = 0.80 / 3
    double expectedQuotedSpread = 0.80 / 3.0;

    assert(
        std::abs(
            bar.getAverageQuotedSpread() -
            expectedQuotedSpread
        ) < 1e-9
    );

    // Effective spreads:
    //
    // Trade 1:
    // midpoint = 100.00
    // effective spread = 0
    //
    // Trade 2:
    // midpoint = 101.00
    // effective spread = 0
    //
    // Trade 3:
    // midpoint = 102.00
    // effective spread = 0
    //
    // Therefore volume-weighted average = 0.
    assert(
        std::abs(bar.getAverageEffectiveSpread()) < 1e-9
    );

    // Average bid size:
    // (200 + 100 + 400) / 3
    double expectedBidSize = 700.0 / 3.0;

    assert(
        std::abs(
            bar.getAverageBidSize() - expectedBidSize
        ) < 1e-9
    );

    // Average ask size:
    // (100 + 300 + 200) / 3 = 200
    assert(
        std::abs(bar.getAverageAskSize() - 200.0) < 1e-9
    );

    // Order imbalance:
    //
    // Trade 1: (200 - 100) / (200 + 100) = 1/3
    // Trade 2: (100 - 300) / (100 + 300) = -1/2
    // Trade 3: (400 - 200) / (400 + 200) = 1/3
    //
    // Average = (1/3 - 1/2 + 1/3) / 3
    double expectedImbalance =
        ((1.0 / 3.0) - (1.0 / 2.0) + (1.0 / 3.0)) / 3.0;

    assert(
        std::abs(
            bar.getAverageOrderImbalance() -
            expectedImbalance
        ) < 1e-9
    );

    std::cout
        << "TBBOBarAggregator tests passed.\n";

    return 0;
}