
#include "MarketDataEngine.h"

void MarketDataEngine::addTrade(const OptionTrade& trade) {
    trades.push_back(trade);
}

int MarketDataEngine::getTradeCount() const {
    return trades.size();
}

int MarketDataEngine::getTotalVolume() const {
    int totalVolume = 0;

    for (const OptionTrade& trade : trades) {
        totalVolume += trade.getSize();
    }

    return totalVolume;
}

double MarketDataEngine::getTotalNotional() const {
    double totalNotional = 0.0;

    for (const OptionTrade& trade : trades) {
        totalNotional += trade.getNotional();
    }

    return totalNotional;
}

int MarketDataEngine::getCallVolume() const {
    int callVolume = 0;

    for (const OptionTrade& trade : trades) {
        if (trade.getOptionType() == 'C') {
            callVolume += trade.getSize();
        }
    }

    return callVolume;
}

int MarketDataEngine::getPutVolume() const {
    int putVolume = 0;

    for (const OptionTrade& trade : trades) {
        if (trade.getOptionType() == 'P') {
            putVolume += trade.getSize();
        }
    }

    return putVolume;
}

double MarketDataEngine::getVWAP() const {
    double totalPriceVolume = 0.0;
    int totalVolume = 0;

    for (const OptionTrade& trade : trades) {
        totalPriceVolume += trade.getPrice() * trade.getSize();
        totalVolume += trade.getSize();
    }

    if (totalVolume == 0) {
        return 0.0;
    }

    return totalPriceVolume / totalVolume;
}

double MarketDataEngine::getPutCallRatio() const {
    int callVolume = getCallVolume();
    int putVolume = getPutVolume();

    if (callVolume == 0) {
        return 0.0;
    }

    return static_cast<double>(putVolume) / callVolume;
}

void MarketDataEngine::reserve(std::size_t capacity) {
    trades.reserve(capacity);
}
