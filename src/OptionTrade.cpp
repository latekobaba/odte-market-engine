
#include "OptionTrade.h"

OptionTrade::OptionTrade(
    long long timestamp,
    const std::string &symbol,
    double strike,
    char optionType,
    double price,
    int size,
    double underlyingPrice)

: timestamp(timestamp),
  symbol(symbol),
  strike(strike),
  optionType(optionType),
  price(price),
  size(size),
  underlyingPrice(underlyingPrice)

{
}

long long OptionTrade::getTimestamp() const {
    return timestamp;
}

const std::string& OptionTrade::getSymbol() const {
    return symbol;
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

double OptionTrade::getUnderlyingPrice() const {
    return underlyingPrice;
}

double OptionTrade::getMoneyness() const {
    return underlyingPrice / strike;
}

double OptionTrade::getNotional() const {
    return price * size * 100;
}