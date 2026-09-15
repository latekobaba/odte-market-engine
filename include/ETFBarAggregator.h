#ifndef ETFBARAGGREGATOR_H
#define ETFBARAGGREGATOR_H

#include <vector>
#include "ETFTrade.h"
#include "ETFBar.h"

class ETFBarAggregator {
public:
    std::vector<ETFBar> aggregate(const std::vector<ETFTrade>& trades) const;
};

#endif