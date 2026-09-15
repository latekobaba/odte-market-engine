

#include "../include/ETFBar.h"
#include <iostream>

ETFBar::ETFBar(
    long long startTimestamp,
    const std::string& symbol,
    int tradeCount,
    long long totalVolume,
    double dollarVolume,
    double vwap,
    double firstPrice,
    double lastPrice,
    long long buyVolume,
    long long sellVolume
)
    : startTimestamp(startTimestamp),
      symbol(symbol),
      tradeCount(tradeCount),
      totalVolume(totalVolume),
      dollarVolume(dollarVolume),
      vwap(vwap),
      firstPrice(firstPrice),
      lastPrice(lastPrice),
      buyVolume(buyVolume),
      sellVolume(sellVolume)
{
}

long long ETFBar::getStartTimestamp() const {
    return startTimestamp;
}

std::string ETFBar::getSymbol() const {
    return symbol;
}

int ETFBar::getTradeCount() const {
    return tradeCount;
}

long long ETFBar::getTotalVolume() const {
    return totalVolume;
}

double ETFBar::getDollarVolume() const {
    return dollarVolume;
}

double ETFBar::getVWAP() const {
    return vwap;
}

double ETFBar::getFirstPrice() const {
    return firstPrice;
}

double ETFBar::getLastPrice() const {
    return lastPrice;
}

long long ETFBar::getBuyVolume() const {
    return buyVolume;
}

long long ETFBar::getSellVolume() const {
    return sellVolume;
}

double ETFBar::getReturn(const ETFBar& previousBar) const {

    if (previousBar.getVWAP() == 0.0) {
        return 0.0;
    }

    return (vwap - previousBar.getVWAP())
           / previousBar.getVWAP();
}

void ETFBar::print() const {
    std::cout << "Start Timestamp: " << startTimestamp << '\n';
    std::cout << "Symbol: " << symbol << '\n';
    std::cout << "Trade Count: " << tradeCount << '\n';
    std::cout << "Total Volume: " << totalVolume << '\n';
    std::cout << "Dollar Volume: " << dollarVolume << '\n';
    std::cout << "VWAP: " << vwap << '\n';
    std::cout << "First Price: " << firstPrice << '\n';
    std::cout << "Last Price: " << lastPrice << '\n';
    std::cout << "Buy Volume: " << buyVolume << '\n';
    std::cout << "Sell Volume: " << sellVolume << '\n';
}