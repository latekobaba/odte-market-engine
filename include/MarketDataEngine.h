
#ifndef MARKETDATAENGINE_H
#define MARKETDATAENGINE_H


#include <vector>
#include <cstddef>
#include "OptionTrade.h"


class MarketDataEngine {

public:
    void addTrade(const OptionTrade& trade);
    void reserve(std::size_t capacity);


    int getTradeCount() const;
    int getTotalVolume() const;
    double getTotalNotional() const;
    int getCallVolume() const;
    int getPutVolume() const;
    double getVWAP() const;
    double getPutCallRatio() const;

private:
    std::vector<OptionTrade> trades;
};

























#endif //MARKETDATAENGINE_H
