#ifndef OPTION_BAR_AGGREGATOR_H
#define OPTION_BAR_AGGREGATOR_H

#include <vector>

#include "OptionTrade.h"
#include "OptionBar.h"

class OptionBarAggregator {
public:
    std::vector<OptionBar> aggregate(
        const std::vector<OptionTrade>& trades
    ) const;
};

#endif