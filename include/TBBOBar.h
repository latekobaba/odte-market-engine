#ifndef TBBOBAR_H
#define TBBOBAR_H

#include <string>

class TBBOBar {
private:
    long long startTimestamp;
    std::string symbol;

    int tradeCount;
    long long totalVolume;
    double dollarVolume;

    double vwap;

    double averageQuotedSpread;
    double averageEffectiveSpread;

    double averageBidSize;
    double averageAskSize;
    double averageOrderImbalance;

public:
    TBBOBar(long long startTimestamp,
            const std::string& symbol,
            int tradeCount,
            long long totalVolume,
            double dollarVolume,
            double vwap,
            double averageQuotedSpread,
            double averageEffectiveSpread,
            double averageBidSize,
            double averageAskSize,
            double averageOrderImbalance);

    long long getStartTimestamp() const;
    const std::string& getSymbol() const;

    int getTradeCount() const;
    long long getTotalVolume() const;
    double getDollarVolume() const;

    double getVWAP() const;

    double getAverageQuotedSpread() const;
    double getAverageEffectiveSpread() const;

    double getAverageBidSize() const;
    double getAverageAskSize() const;
    double getAverageOrderImbalance() const;

    void print() const;
};

#endif