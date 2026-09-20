#include "TBBOTrade.h"

#include <cmath>

TBBOTrade::TBBOTrade(long long timestamp,
                     const std::string& symbol,
                     double price,
                     int size,
                     char side,
                     double bidPrice,
                     double askPrice,
                     int bidSize,
                     int askSize)
    : timestamp(timestamp),
      symbol(symbol),
      price(price),
      size(size),
      side(side),
      bidPrice(bidPrice),
      askPrice(askPrice),
      bidSize(bidSize),
      askSize(askSize) {
}

long long TBBOTrade::getTimestamp() const {
    return timestamp;
}

const std::string& TBBOTrade::getSymbol() const {
    return symbol;
}

double TBBOTrade::getPrice() const {
    return price;
}

int TBBOTrade::getSize() const {
    return size;
}

char TBBOTrade::getSide() const {
    return side;
}

double TBBOTrade::getBidPrice() const {
    return bidPrice;
}

double TBBOTrade::getAskPrice() const {
    return askPrice;
}

int TBBOTrade::getBidSize() const {
    return bidSize;
}

int TBBOTrade::getAskSize() const {
    return askSize;
}

double TBBOTrade::getMidPrice() const {
    return (bidPrice + askPrice) / 2.0;
}

double TBBOTrade::getQuotedSpread() const {
    return askPrice - bidPrice;
}

double TBBOTrade::getEffectiveSpread() const {
    return 2.0 * std::abs(price - getMidPrice());
}

double TBBOTrade::getNotional() const {
    return price * size;
}