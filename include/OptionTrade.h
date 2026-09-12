#ifndef OPTION_TRADE_H
#define OPTION_TRADE_H


#include <string>

class OptionTrade{
public:
    OptionTrade(
        long long timestamp,
        const std:: string& symbol,
        double strike,
        char OptionType,
        double price,
        int size,
        double underlyingprice
);
    long long getTimestamp() const;
    const std::string& getSymbol() const;
    double getStrike() const;
    char getOptionType() const;
    double getPrice() const;
    int getSize() const;
    double getUnderlyingPrice() const;
    double getMoneyness() const;
    double getNotional() const;


private:
    long long timestamp;
    std::string symbol;
    double strike;
    char optionType;
    double price;
    int size;
    double underlyingPrice;

};

#endif
