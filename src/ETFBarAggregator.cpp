#include "../include/ETFBarAggregator.h"

std::vector<ETFBar> ETFBarAggregator::aggregate(
    const std::vector<ETFTrade>& trades
) const {

    std::vector<ETFBar> bars;

    if (trades.empty()) {
        return bars;
    }

    // Databento timestamps are in nanoseconds.
    // 5 minutes = 300 seconds = 300,000,000,000 nanoseconds.
    const long long FIVE_MINUTES_NS = 300000000000LL;

    long long currentBucketStart =
        (trades[0].getTimestamp() / FIVE_MINUTES_NS) * FIVE_MINUTES_NS;

    std::string currentSymbol = trades[0].getSymbol();

    int tradeCount = 0;
    long long totalVolume = 0;

    double dollarVolume = 0.0;

    double firstPrice = trades[0].getPrice();
    double lastPrice = trades[0].getPrice();

    long long buyVolume = 0;
    long long sellVolume = 0;

    for (const ETFTrade& trade : trades) {

        long long bucketStart =
            (trade.getTimestamp() / FIVE_MINUTES_NS) * FIVE_MINUTES_NS;

        // Have we moved into a new 5-minute interval?
        if (bucketStart != currentBucketStart) {

            double vwap = 0.0;

            if (totalVolume > 0) {
                vwap = dollarVolume / totalVolume;
            }

            bars.emplace_back(
                currentBucketStart,
                currentSymbol,
                tradeCount,
                totalVolume,
                dollarVolume,
                vwap,
                firstPrice,
                lastPrice,
                buyVolume,
                sellVolume
            );

            // Reset everything for the new interval.
            currentBucketStart = bucketStart;
            currentSymbol = trade.getSymbol();

            tradeCount = 0;
            totalVolume = 0;
            dollarVolume = 0.0;

            firstPrice = trade.getPrice();
            lastPrice = trade.getPrice();

            buyVolume = 0;
            sellVolume = 0;
        }

        ++tradeCount;

        totalVolume += trade.getSize();

        dollarVolume +=
            trade.getPrice() * trade.getSize();

        lastPrice = trade.getPrice();

        if (trade.getSide() == 'B') {
            buyVolume += trade.getSize();
        }
        else if (trade.getSide() == 'A') {
            sellVolume += trade.getSize();
        }
    }

    // Save the final interval.
    double vwap = 0.0;

    if (totalVolume > 0) {
        vwap = dollarVolume / totalVolume;
    }

    bars.emplace_back(
        currentBucketStart,
        currentSymbol,
        tradeCount,
        totalVolume,
        dollarVolume,
        vwap,
        firstPrice,
        lastPrice,
        buyVolume,
        sellVolume
    );

    return bars;
}