

#include "ETFTrade.h"
#include <iostream>


ETFTrade::ETFTrade(
    long long timestamp,
    const std::string& symbol,
    double price,
    int size,
    char side,
    long long sequence)
    : timestamp(timestamp),
      symbol(symbol),
      price(price),
      size(size),
      side(side),
      sequence(sequence)
{
}

long long ETFTrade::getTimestamp() const {
    return timestamp;
}

const std::string& ETFTrade::getSymbol() const {
    return symbol;
}

double ETFTrade::getPrice() const {
    return price;
}

int ETFTrade::getSize() const {
    return size;
}

char ETFTrade::getSide() const {
    return side;
}

long long ETFTrade::getSequence() const {
    return sequence;
}

double ETFTrade::getNotional() const {
    return price * size;
}

void ETFTrade::print() const {
    std::cout << "Timestamp: " << timestamp << '\n';
    std::cout << "Symbol: " << symbol << '\n';
    std::cout << "Price: " << price << '\n';
    std::cout << "Size: " << size << '\n';
    std::cout << "Side: " << side << '\n';
    std::cout << "Sequence: " << sequence << '\n';
    std::cout << "Notional: " << getNotional() << '\n';
}