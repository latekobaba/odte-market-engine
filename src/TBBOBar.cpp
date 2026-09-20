#include "TBBOBar.h"

#include <iostream>


TBBOBar::TBBOBar(long long startTimestamp,
                 const std::string& symbol,
                 int tradeCount,
                 long long totalVolume,
                 double dollarVolume,
                 double vwap,
                 double averageQuotedSpread,
                 double averageEffectiveSpread,
                 double averageBidSize,
                 double averageAskSize,
                 double averageOrderImbalance)
    : startTimestamp(startTimestamp),
      symbol(symbol),
      tradeCount(tradeCount),
      totalVolume(totalVolume),
      dollarVolume(dollarVolume),
      vwap(vwap),
      averageQuotedSpread(averageQuotedSpread),
      averageEffectiveSpread(averageEffectiveSpread),
      averageBidSize(averageBidSize),
      averageAskSize(averageAskSize),
      averageOrderImbalance(averageOrderImbalance) {
}


long long TBBOBar::getStartTimestamp() const {
    return startTimestamp;
}


const std::string& TBBOBar::getSymbol() const {
    return symbol;
}


int TBBOBar::getTradeCount() const {
    return tradeCount;
}


long long TBBOBar::getTotalVolume() const {
    return totalVolume;
}


double TBBOBar::getDollarVolume() const {
    return dollarVolume;
}


double TBBOBar::getVWAP() const {
    return vwap;
}


double TBBOBar::getAverageQuotedSpread() const {
    return averageQuotedSpread;
}


double TBBOBar::getAverageEffectiveSpread() const {
    return averageEffectiveSpread;
}


double TBBOBar::getAverageBidSize() const {
    return averageBidSize;
}


double TBBOBar::getAverageAskSize() const {
    return averageAskSize;
}


double TBBOBar::getAverageOrderImbalance() const {
    return averageOrderImbalance;
}


void TBBOBar::print() const {

    std::cout << "Start Timestamp: "
              << startTimestamp << '\n';

    std::cout << "Symbol: "
              << symbol << '\n';

    std::cout << "Trade Count: "
              << tradeCount << '\n';

    std::cout << "Total Volume: "
              << totalVolume << '\n';

    std::cout << "Dollar Volume: "
              << dollarVolume << '\n';

    std::cout << "VWAP: "
              << vwap << '\n';

    std::cout << "Average Quoted Spread: "
              << averageQuotedSpread << '\n';

    std::cout << "Average Effective Spread: "
              << averageEffectiveSpread << '\n';

    std::cout << "Average Bid Size: "
              << averageBidSize << '\n';

    std::cout << "Average Ask Size: "
              << averageAskSize << '\n';

    std::cout << "Average Order Imbalance: "
              << averageOrderImbalance << '\n';
}