#ifndef OPTION_BAR_H
#define OPTION_BAR_H

#include <string>

class OptionBar {
public:
    OptionBar(
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
    );

    const std::string& getStartTimestamp() const;
    const std::string& getSymbol() const;

    int getTradeCount() const;
    int getTotalVolume() const;

    double getTotalNotional() const;

    int getCallVolume() const;
    int getPutVolume() const;

    double getVWAP() const;
    double getAverageSpread() const;
    double getAverageIV() const;
    double getAverageDelta() const;
    double getAverageGamma() const;

    double getPutCallRatio() const;
    double getAverageATMDistance() const;

private:
    std::string startTimestamp;
    std::string symbol;

    int tradeCount;
    int totalVolume;

    double totalNotional;

    int callVolume;
    int putVolume;

    double vwap;
    double averageSpread;
    double averageIV;
    double averageDelta;
    double averageGamma;

    double averageATMDistance;
};

#endif