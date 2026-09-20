#ifndef TBBOTRADE_H
#define TBBOTRADE_H

#include <string>

class TBBOTrade {
private:
    long long timestamp;
    std::string symbol;
    double price;
    int size;
    char side;

    double bidPrice;
    double askPrice;
    int bidSize;
    int askSize;

public:
    TBBOTrade(long long timestamp,
              const std::string& symbol,
              double price,
              int size,
              char side,
              double bidPrice,
              double askPrice,
              int bidSize,
              int askSize);

    long long getTimestamp() const;
    const std::string& getSymbol() const;
    double getPrice() const;
    int getSize() const;
    char getSide() const;

    double getBidPrice() const;
    double getAskPrice() const;
    int getBidSize() const;
    int getAskSize() const;

    double getMidPrice() const;
    double getQuotedSpread() const;
    double getEffectiveSpread() const;
    double getNotional() const;
};

#endif