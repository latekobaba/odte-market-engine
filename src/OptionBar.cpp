#include "OptionBar.h"

#include <limits>

OptionBar::OptionBar(
    const std::string& startTimestamp,
    const std::string& symbol,
    int tradeCount,
    int totalVolume,
    double totalNotional,
    int callVolume,
    int putVolume,
    double vwap,
    double averageSpread,
    double averageIV,
    double averageDelta,
    double averageGamma,
    double averageATMDistance
)
    : startTimestamp(startTimestamp),
      symbol(symbol),
      tradeCount(tradeCount),
      totalVolume(totalVolume),
      totalNotional(totalNotional),
      callVolume(callVolume),
      putVolume(putVolume),
      vwap(vwap),
      averageSpread(averageSpread),
      averageIV(averageIV),
      averageDelta(averageDelta),
      averageGamma(averageGamma),
      averageATMDistance(averageATMDistance)
{
}

const std::string& OptionBar::getStartTimestamp() const {
    return startTimestamp;
}

const std::string& OptionBar::getSymbol() const {
    return symbol;
}

int OptionBar::getTradeCount() const {
    return tradeCount;
}

int OptionBar::getTotalVolume() const {
    return totalVolume;
}

double OptionBar::getTotalNotional() const {
    return totalNotional;
}

int OptionBar::getCallVolume() const {
    return callVolume;
}

int OptionBar::getPutVolume() const {
    return putVolume;
}

double OptionBar::getVWAP() const {
    return vwap;
}

double OptionBar::getAverageSpread() const {
    return averageSpread;
}

double OptionBar::getAverageIV() const {
    return averageIV;
}

double OptionBar::getAverageDelta() const {
    return averageDelta;
}

double OptionBar::getAverageGamma() const {
    return averageGamma;
}

double OptionBar::getPutCallRatio() const {
    if (callVolume == 0) {
        return std::numeric_limits<double>::infinity();
    }

    return static_cast<double>(putVolume) /
           static_cast<double>(callVolume);
}

double OptionBar::getAverageATMDistance() const {
    return averageATMDistance;
}