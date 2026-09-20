#include "TBBOTrade.h"
#include "TBBOBar.h"
#include "TBBOBarAggregator.h"
#include "OptionTrade.h"
#include "OptionBar.h"
#include "OptionBarAggregator.h"

#include <cassert>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main() {

    // ========================================================
    // 1. Create TBBO trades in the 09:30 SPY interval
    // ========================================================

    std::vector<TBBOTrade> tbboTrades;

    tbboTrades.emplace_back(
        1672756200020029081LL,
        "SPY",
        384.37,
        200,
        'A',
        384.37,
        384.39,
        200,
        100
    );

    TBBOBarAggregator tbboAggregator;

    std::vector<TBBOBar> tbboBars =
        tbboAggregator.aggregate(tbboTrades);

    assert(tbboBars.size() == 1);


    // ========================================================
    // 2. Create a CBOE 0DTE option trade in same interval
    // ========================================================

    std::vector<OptionTrade> optionTrades;

    optionTrades.emplace_back(
        "2023-01-03 09:30:30.000",
        "SPY",
        "2023-01-03",
        384.0,
        'C',
        1.00,
        10,
        0.95,
        1.05,
        0.25,
        0.50,
        0.10,
        384.36,
        384.38
    );

    OptionBarAggregator optionAggregator;

    std::vector<OptionBar> optionBars =
        optionAggregator.aggregate(optionTrades);

    assert(optionBars.size() == 1);


    // ========================================================
    // 3. Build lookup for SPY option bars
    // ========================================================

    std::map<std::string, const OptionBar*> optionBarMap;

    for (const OptionBar& bar : optionBars) {
        if (bar.getSymbol() == "SPY") {
            optionBarMap[bar.getStartTimestamp()] = &bar;
        }
    }


    // ========================================================
    // 4. Convert TBBO nanosecond timestamp to Eastern time
    //
    // Jan 3, 2023 is EST = UTC - 5 hours.
    // This intentionally matches the current integration logic
    // used by Project 1 for the Jan 2023 validation dataset.
    // ========================================================

    const TBBOBar& tbboBar = tbboBars[0];

    long long seconds =
        tbboBar.getStartTimestamp() / 1000000000LL;

    seconds -= 5 * 60 * 60;

    std::time_t timeValue =
        static_cast<std::time_t>(seconds);

    std::tm* timeInfo = std::gmtime(&timeValue);

    assert(timeInfo != nullptr);

    std::ostringstream timestampStream;

    timestampStream
        << std::put_time(
            timeInfo,
            "%Y-%m-%d %H:%M"
        );

    std::string optionTimestamp =
        timestampStream.str();


    // ========================================================
    // 5. Verify the two market-data layers match
    // ========================================================

    assert(optionTimestamp == "2023-01-03 09:30");

    auto match =
        optionBarMap.find(optionTimestamp);

    assert(match != optionBarMap.end());

    const OptionBar* matchedOptionBar =
        match->second;

    assert(matchedOptionBar != nullptr);
    assert(matchedOptionBar->getSymbol() == "SPY");

    std::cout
        << "Market integration tests passed.\n";

    return 0;
}