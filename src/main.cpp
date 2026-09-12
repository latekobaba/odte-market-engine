

#include <iostream>
#include <vector>
#include "OptionTrade.h"
#include "MarketDataEngine.h"


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

    MarketDataEngine engine;
    for (const OptionTrade& t : trades) {
        engine.addTrade(t);
    }

    std::cout << "Engine Trade Count: "
          << engine.getTradeCount() << '\n';

    std::cout << "Engine Total Volume: "
          << engine.getTotalVolume() << '\n';

    std::cout << "Engine Total Notional: "
              << engine.getTotalNotional() << '\n';

    std::cout << "Engine Call Volume: "
              << engine.getCallVolume() << '\n';

    std::cout << "Engine Put Volume: "
              << engine.getPutVolume() << '\n';

    std::cout << "Engine VWAP: "
              << engine.getVWAP() << '\n';

    std::cout << "Engine Put/Call Ratio: "
          << engine.getPutCallRatio() << '\n';



#ifdef __linux__
    std::cout << "Platform: Linux\n";
#elif _WIN32
    std::cout << "Platform: Windows\n";
#endif


    // loop through the vector
    for (const OptionTrade& t : trades) {


        std::cout << "\nTrade\n";
        std::cout << "Symbol: " << t.getSymbol() << '\n';
        std::cout << "Strike: " << t.getStrike() << '\n';
        std::cout << "Option Type: " << t.getOptionType() << '\n';
        std::cout << "Price: " << t.getPrice() << '\n';
        std::cout << "Size: " << t.getSize() << '\n';
        std::cout << "Moneyness: " << t.getMoneyness() << '\n';
        std::cout << "Notional: " << t.getNotional() << '\n';

    }

    return 0;
}