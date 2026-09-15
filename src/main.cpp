

#include <iostream>
#include <vector>
#include <chrono>

#include "OptionTrade.h"
#include "MarketDataEngine.h"
#include "ETFTradeParser.h"
#include "../include/ETFBarAggregator.h"

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

    engine.reserve(3);


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

    ETFTradeParser parser;

    auto parseStart = std::chrono::high_resolution_clock::now();

    std::vector<ETFTrade> etfTrades =
        parser.parseFile("data/etf_trades_large.csv");

    auto parseEnd = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> parseTime =
        parseEnd - parseStart;

    std::cout << "\nParsed ETF Trades: " << etfTrades.size() << '\n';

    std::cout << "ETF Parse Time: "
          << parseTime.count()
          << " seconds\n";

    double parseThroughput =
    etfTrades.size() / parseTime.count();

    std::cout << "ETF Parse Throughput: "
              << parseThroughput
              << " trades/second\n";

    /*
    for (const ETFTrade& trade : etfTrades) {
        trade.print();
        std::cout << '\n';
    }
*/

    ETFBarAggregator aggregator;

    auto aggregationStart =
        std::chrono::high_resolution_clock::now();

    std::vector<ETFBar> bars =
        aggregator.aggregate(etfTrades);

    auto aggregationEnd =
        std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> aggregationTime =
        aggregationEnd - aggregationStart;


    std::cout << "\n5-Minute ETF Bars: "
              << bars.size()
              << "\n\n";

    std::cout << "ETF Aggregation Time: "
          << aggregationTime.count()
          << " seconds\n\n";


    for (const ETFBar& bar : bars) {
        bar.print();
        std::cout << '\n';
    }


    std::cout << "\nETF 5-Minute Return Series:\n";

    for (std::size_t i = 1; i < bars.size(); ++i) {

        double etfReturn =
            bars[i].getReturn(bars[i - 1]);

        std::cout << "Interval " << i
                  << " Return: "
                  << etfReturn
                  << '\n';
    }

    return 0;
}