#include "MarketBarAggregator.h"

#include <ctime>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <utility>


namespace {

    std::string etfTimestampToEasternMinute(
        long long timestampNanoseconds
    ) {

        // Convert nanoseconds since Unix epoch to seconds
        std::time_t seconds =
            static_cast<std::time_t>(
                timestampNanoseconds / 1000000000LL
            );

        // January 2023:
        // Eastern Standard Time = UTC - 5 hours
        seconds -= 5 * 60 * 60;

        std::tm easternTime =
            *std::gmtime(&seconds);

        std::ostringstream output;

        output << std::put_time(
            &easternTime,
            "%Y-%m-%d %H:%M"
        );

        return output.str();
    }

}


std::vector<MarketBar> MarketBarAggregator::aggregate(
    const std::vector<ETFBar>& etfBars,
    const std::vector<OptionBar>& optionBars
) const {

    std::vector<MarketBar> marketBars;


    // ---------------------------------------------------------
    // Integration key:
    //      symbol + 5-minute timestamp
    //
    // Example:
    //      SPY | 2023-01-03 09:30
    //      QQQ | 2023-01-03 09:30
    // ---------------------------------------------------------

    using MarketKey =
        std::pair<std::string, std::string>;


    // ---------------------------------------------------------
    // Index option bars by symbol + timestamp
    // ---------------------------------------------------------

    std::map<
        MarketKey,
        const OptionBar*
    > optionBarMap;


    for (const OptionBar& optionBar : optionBars) {

        MarketKey key{
            optionBar.getSymbol(),
            optionBar.getStartTimestamp()
        };

        optionBarMap[key] =
            &optionBar;
    }


    // ---------------------------------------------------------
    // Walk through ETF bars and find the corresponding
    // option bar with BOTH the same symbol and timestamp
    // ---------------------------------------------------------

    for (const ETFBar& etfBar : etfBars) {

        std::string etfTimestamp =
            etfTimestampToEasternMinute(
                etfBar.getStartTimestamp()
            );


        MarketKey key{
            etfBar.getSymbol(),
            etfTimestamp
        };


        auto match =
            optionBarMap.find(key);


        if (match != optionBarMap.end()) {

            marketBars.emplace_back(
                etfBar,
                *(match->second)
            );
        }
    }


    return marketBars;
}