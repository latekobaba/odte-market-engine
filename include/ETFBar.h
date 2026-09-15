//
// Created by talk2 on 9/14/2026.
//

#ifndef ETFBAR_H
#define ETFBAR_H




#include <string>

class ETFBar {
private:
    long long startTimestamp;
    std::string symbol;

    int tradeCount;
    long long totalVolume;

    double dollarVolume;
    double vwap;

    double firstPrice;
    double lastPrice;

    long long buyVolume;
    long long sellVolume;

public:
    ETFBar(
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
    );

    long long getStartTimestamp() const;
    std::string getSymbol() const;

    int getTradeCount() const;
    long long getTotalVolume() const;

    double getDollarVolume() const;
    double getVWAP() const;

    double getFirstPrice() const;
    double getLastPrice() const;

    long long getBuyVolume() const;
    long long getSellVolume() const;

    double getReturn(const ETFBar& previousBar) const;

    void print() const;
};

#endif //ETFBAR_H
