#include "MarketBar.h"

MarketBar::MarketBar(
    const ETFBar& etfBar,
    const OptionBar& optionBar
)
    : etfBar(etfBar),
      optionBar(optionBar)
{
}

const ETFBar& MarketBar::getETFBar() const {
    return etfBar;
}

const OptionBar& MarketBar::getOptionBar() const {
    return optionBar;
}