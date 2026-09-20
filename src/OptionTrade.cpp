#include "OptionTrade.h"

OptionTrade::OptionTrade(
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
)
    : timestamp(timestamp),
      symbol(symbol),
      expiration(expiration),
      strike(strike),
      optionType(optionType),
      price(price),
      size(size),
      bestBid(bestBid),
      bestAsk(bestAsk),
      impliedVolatility(impliedVolatility),
      delta(delta),
      gamma(gamma),
      underlyingBid(underlyingBid),
      underlyingAsk(underlyingAsk)
{
}

const std::string& OptionTrade::getTimestamp() const {
    return timestamp;
}

const std::string& OptionTrade::getSymbol() const {
    return symbol;
}

const std::string& OptionTrade::getExpiration() const {
    return expiration;
}

double OptionTrade::getStrike() const {
    return strike;
}

char OptionTrade::getOptionType() const {
    return optionType;
}

double OptionTrade::getPrice() const {
    return price;
}

int OptionTrade::getSize() const {
    return size;
}

double OptionTrade::getBestBid() const {
    return bestBid;
}

double OptionTrade::getBestAsk() const {
    return bestAsk;
}

double OptionTrade::getImpliedVolatility() const {
    return impliedVolatility;
}

double OptionTrade::getDelta() const {
    return delta;
}

double OptionTrade::getGamma() const {
    return gamma;
}

double OptionTrade::getUnderlyingBid() const {
    return underlyingBid;
}

double OptionTrade::getUnderlyingAsk() const {
    return underlyingAsk;
}

double OptionTrade::getUnderlyingPrice() const {
    return (underlyingBid + underlyingAsk) / 2.0;
}

double OptionTrade::getMoneyness() const {
    return getUnderlyingPrice() / strike;
}

double OptionTrade::getNotional() const {
    return price * size * 100;
}