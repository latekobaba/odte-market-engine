#include "OptionTrade.h"
#include "OptionBar.h"
#include "OptionBarAggregator.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

int main() {

    std::vector<OptionTrade> trades;

    // Three SPY 0DTE trades in the same 09:30 five-minute interval.
    trades.emplace_back(
        "2023-01-03 09:30:10.000",
        "SPY",
        "2023-01-03",
        380.0,
        'C',
        2.00,
        10,
        1.90,
        2.10,
        0.20,
        0.50,
        0.08,
        379.90,
        380.10
    );

    trades.emplace_back(
        "2023-01-03 09:31:20.000",
        "SPY",
        "2023-01-03",
        380.0,
        'P',
        3.00,
        20,
        2.80,
        3.20,
        0.30,
        -0.50,
        0.10,
        379.90,
        380.10
    );

    trades.emplace_back(
        "2023-01-03 09:34:50.000",
        "SPY",
        "2023-01-03",
        380.0,
        'C',
        4.00,
        30,
        3.90,
        4.10,
        0.40,
        0.60,
        0.12,
        379.90,
        380.10
    );

    OptionBarAggregator aggregator;

    std::vector<OptionBar> bars =
        aggregator.aggregate(trades);

    // All three trades belong to one five-minute bar.
    assert(bars.size() == 1);

    const OptionBar& bar = bars[0];

    assert(bar.getSymbol() == "SPY");
    assert(bar.getStartTimestamp() == "2023-01-03 09:30");

    assert(bar.getTradeCount() == 3);

    // Volume:
    // 10 + 20 + 30 = 60
    assert(bar.getTotalVolume() == 60);

    // Call volume:
    // 10 + 30 = 40
    assert(bar.getCallVolume() == 40);

    // Put volume:
    // 20
    assert(bar.getPutVolume() == 20);

    // VWAP:
    // (2*10 + 3*20 + 4*30) / 60
    // = 200 / 60
    double expectedVWAP = 200.0 / 60.0;

    assert(
        std::abs(bar.getVWAP() - expectedVWAP) < 1e-9
    );

    // Notional:
    // 2*10*100 + 3*20*100 + 4*30*100
    // = 20,000
    assert(
        std::abs(bar.getTotalNotional() - 20000.0) < 1e-9
    );

    // Average quoted spread:
    // 0.20 + 0.40 + 0.20 = 0.80
    // 0.80 / 3
    double expectedSpread = 0.8 / 3.0;

    assert(
        std::abs(
            bar.getAverageSpread() - expectedSpread
        ) < 1e-9
    );

    // Average IV:
    // (0.20 + 0.30 + 0.40) / 3 = 0.30
    assert(
        std::abs(bar.getAverageIV() - 0.30) < 1e-9
    );

    // Average delta:
    // (0.50 - 0.50 + 0.60) / 3 = 0.20
    assert(
        std::abs(bar.getAverageDelta() - 0.20) < 1e-9
    );

    // Average gamma:
    // (0.08 + 0.10 + 0.12) / 3 = 0.10
    assert(
        std::abs(bar.getAverageGamma() - 0.10) < 1e-9
    );

    // Put/call ratio:
    // 20 / 40 = 0.50
    assert(
        std::abs(bar.getPutCallRatio() - 0.50) < 1e-9
    );

    // Underlying midpoint = 380
    // Strike = 380
    // Moneyness = 1
    // ATM distance = |1 - 1| = 0
    assert(
        std::abs(bar.getAverageATMDistance()) < 1e-9
    );

    std::cout
        << "OptionBarAggregator tests passed.\n";

    return 0;
}