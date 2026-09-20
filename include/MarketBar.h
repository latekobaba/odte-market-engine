#ifndef MARKET_BAR_H
#define MARKET_BAR_H

#include "ETFBar.h"
#include "OptionBar.h"

class MarketBar {
public:
    MarketBar(
        const ETFBar& etfBar,
        const OptionBar& optionBar
    );

    const ETFBar& getETFBar() const;
    const OptionBar& getOptionBar() const;

private:
    ETFBar etfBar;
    OptionBar optionBar;
};

#endif