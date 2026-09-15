

#ifndef ETFTRADE_H
#define ETFTRADE_H

#include <string>

class ETFTrade {
public:
    ETFTrade(
        long long timestamp,
        const std::string& symbol,
        double price,
        int size,
        char side,
        long long sequence
    );

    long long getTimestamp() const;
    const std::string& getSymbol() const;
    double getPrice() const;
    int getSize() const;
    char getSide() const;
    long long getSequence() const;
    double getNotional() const;
    void print() const;

private:
    long long timestamp;
    std::string symbol;
    double price;
    int size;
    char side;
    long long sequence;
};



#endif // ETFTRADE_H