#include "TBBOTrade.h"

#include <cassert>
#include <cmath>
#include <iostream>

int main() {

    TBBOTrade trade(
        1672756200020029081LL,  // timestamp
        "SPY",
        384.37,                 // trade price
        200,                    // size
        'A',                    // side
        384.37,                 // bid
        384.39,                 // ask
        200,                    // bid size
        100                     // ask size
    );

    // --------------------------------------------------------
    // Stored values
    // --------------------------------------------------------

    assert(trade.getTimestamp() == 1672756200020029081LL);
    assert(trade.getSymbol() == "SPY");
    assert(std::abs(trade.getPrice() - 384.37) < 1e-9);
    assert(trade.getSize() == 200);
    assert(trade.getSide() == 'A');

    assert(std::abs(trade.getBidPrice() - 384.37) < 1e-9);
    assert(std::abs(trade.getAskPrice() - 384.39) < 1e-9);

    assert(trade.getBidSize() == 200);
    assert(trade.getAskSize() == 100);

    // --------------------------------------------------------
    // Derived values
    // --------------------------------------------------------

    // Mid = (384.37 + 384.39) / 2 = 384.38
    assert(
        std::abs(trade.getMidPrice() - 384.38) < 1e-9
    );

    // Quoted spread = ask - bid = 0.02
    assert(
        std::abs(trade.getQuotedSpread() - 0.02) < 1e-9
    );

    // Effective spread:
    // 2 * |trade price - midpoint|
    // = 2 * |384.37 - 384.38|
    // = 0.02
    assert(
        std::abs(trade.getEffectiveSpread() - 0.02) < 1e-9
    );

    // Notional = price * size
    // = 384.37 * 200
    // = 76,874
    assert(
        std::abs(trade.getNotional() - 76874.0) < 1e-9
    );

    std::cout << "TBBOTrade tests passed.\n";

    return 0;
}