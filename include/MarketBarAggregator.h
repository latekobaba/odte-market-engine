#ifndef MARKET_BAR_AGGREGATOR_H
#define MARKET_BAR_AGGREGATOR_H

#include <vector>

#include "ETFBar.h"
#include "OptionBar.h"
#include "MarketBar.h"

class MarketBarAggregator {
public:
    std::vector<MarketBar> aggregate(
        const std::vector<ETFBar>& etfBars,
        const std::vector<OptionBar>& optionBars
    ) const;
};

#endif