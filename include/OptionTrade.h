#ifndef OPTION_TRADE_H
#define OPTION_TRADE_H


#include <string>

class OptionTrade{
public:
    OptionTrade(
        const std::string& timestamp,
        const std::string& symbol,
        const std::string& expiration,
        double strike,
        char optionType,
        double price,
        int size,
        double bestBid,
        double bestAsk,
        double impliedVolatility,
        double delta,
        double gamma,
        double underlyingBid,
        double underlyingAsk
    );

    const std::string& getTimestamp() const;
    const std::string& getSymbol() const;
    const std::string& getExpiration() const;
    double getStrike() const;
    char getOptionType() const;
    double getPrice() const;
    int getSize() const;
    double getBestBid() const;
    double getBestAsk() const;
    double getImpliedVolatility() const;
    double getDelta() const;
    double getGamma() const;
    double getUnderlyingBid() const;
    double getUnderlyingAsk() const;
    double getUnderlyingPrice() const;
    double getMoneyness() const;
    double getNotional() const;



private:
    std::string timestamp;
    std::string symbol;
    std::string expiration;
    double strike;
    char optionType;
    double price;
    int size;
    double bestBid;
    double bestAsk;
    double impliedVolatility;
    double delta;
    double gamma;
    double underlyingBid;
    double underlyingAsk;

};

#endif
