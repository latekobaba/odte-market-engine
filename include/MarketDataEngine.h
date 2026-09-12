
#ifndef MARKETDATAENGINE_H
#define MARKETDATAENGINE_H


#include <vector>
#include "OptionTrade.h"


class MarketDataEngine {

public:
    void addTrade(const OptionTrade& trade);

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
