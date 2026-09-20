#include "OptionTrade.h"

#include <cassert>
#include <cmath>
#include <iostream>

int main() {

    OptionTrade trade(
        "2023-01-03 09:30:00.000",
        "SPY",
        "2023-01-03",
        380.0,      // strike
        'C',        // option type
        2.50,       // option price
        10,         // size
        2.40,       // best bid
        2.60,       // best ask
        0.25,       // IV
        0.55,       // delta
        0.08,       // gamma
        383.90,     // underlying bid
        384.10      // underlying ask
    );

    // Basic stored values
    assert(trade.getSymbol() == "SPY");
    assert(trade.getExpiration() == "2023-01-03");
    assert(trade.getStrike() == 380.0);
    assert(trade.getOptionType() == 'C');
    assert(trade.getPrice() == 2.50);
    assert(trade.getSize() == 10);

    // Derived values
    double expectedUnderlyingPrice = 384.0;
    double expectedMoneyness = 384.0 / 380.0;
    double expectedNotional = 2.50 * 10 * 100;

    assert(std::abs(
        trade.getUnderlyingPrice() - expectedUnderlyingPrice
    ) < 1e-9);

    assert(std::abs(
        trade.getMoneyness() - expectedMoneyness
    ) < 1e-9);

    assert(std::abs(
        trade.getNotional() - expectedNotional
    ) < 1e-9);

    std::cout << "OptionTrade tests passed.\n";

    return 0;
}