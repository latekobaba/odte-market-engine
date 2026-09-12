

#include <iostream>
#include <vector>
#include "OptionTrade.h"


int main() {
    OptionTrade trade(
        34200123456789,
        "SPY",
        550.0,
        'C',
        2.35,
        100,
        551.25
    );

// creates a container capable of holding many OptionTrade objects:
//This is the beginning of the transition from a demonstration program to a market-data engine.
    std::vector<OptionTrade> trades;

    // Take the trade object and add it to the end of the trades vector.
    trades.push_back(trade);

    trades.emplace_back(
        34200123500000,
        "SPY",
        552.0,
        'C',
        1.85,
        50,
        551.30
);

    trades.emplace_back(
        34200123600000,
        "SPY",
        548.0,
        'P',
        1.40,
        75,
        551.20
    );


#ifdef __linux__
    std::cout << "Platform: Linux\n";
#elif _WIN32
    std::cout << "Platform: Windows\n";
#endif


    // aggregation variables:
    int totalVolume = 0;
    double totalNotional = 0.0;
    int callVolume = 0;
    int putVolume = 0;
    double totalPriceVolume = 0.0;
    int tradeCount = 0;

    // loop through the vector
    for (const OptionTrade& t : trades) {

        totalVolume += t.getSize();
        totalNotional += t.getNotional();

        if (t.getOptionType() == 'C') {
            callVolume += t.getSize();
        }
        else if (t.getOptionType() == 'P') {
            putVolume += t.getSize();
        }

        totalPriceVolume += t.getPrice() * t.getSize();

        tradeCount++;

        std::cout << "\nTrade\n";
        std::cout << "Symbol: " << t.getSymbol() << '\n';
        std::cout << "Strike: " << t.getStrike() << '\n';
        std::cout << "Option Type: " << t.getOptionType() << '\n';
        std::cout << "Price: " << t.getPrice() << '\n';
        std::cout << "Size: " << t.getSize() << '\n';
        std::cout << "Moneyness: " << t.getMoneyness() << '\n';
        std::cout << "Notional: " << t.getNotional() << '\n';

    }

    std::cout << "\nTotal Volume: " << totalVolume << '\n';
    std::cout << "Total Notional: " << totalNotional << '\n';

    std::cout << "Call Volume: " << callVolume << '\n';
    std::cout << "Put Volume: " << putVolume << '\n';

    double putCallRatio = 0.0;
    if (callVolume != 0) {
        putCallRatio =
            static_cast<double>(putVolume) / callVolume;

    }
    std::cout << "Put/Call Volume Ratio: " << putCallRatio << '\n';

    double vwap = 0.0;
    if (totalVolume != 0) {
        vwap = totalPriceVolume / totalVolume;
    }
    std::cout << "VWAP: " << vwap << '\n';

    std::cout << "Trade Count: " << tradeCount << '\n';

    return 0;
}