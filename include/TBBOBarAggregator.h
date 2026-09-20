#ifndef TBBOBARAGGREGATOR_H
#define TBBOBARAGGREGATOR_H

#include <vector>

#include "TBBOTrade.h"
#include "TBBOBar.h"


class TBBOBarAggregator {
public:
    std::vector<TBBOBar> aggregate(
        const std::vector<TBBOTrade>& trades
    ) const;
};

#endif