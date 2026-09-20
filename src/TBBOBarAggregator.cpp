#include "TBBOBarAggregator.h"

#include <map>
#include <string>
#include <utility>


std::vector<TBBOBar> TBBOBarAggregator::aggregate(
    const std::vector<TBBOTrade>& trades
) const {

    // 5 minutes in nanoseconds
    const long long FIVE_MINUTES_NS =
        300000000000LL;


    // ---------------------------------------------------------
    // Temporary statistics accumulated for each 5-minute bar
    // ---------------------------------------------------------

    struct BarData {

        int tradeCount = 0;

        long long totalVolume = 0;

        double dollarVolume = 0.0;

        // For trade-weighted quoted spread
        double quotedSpreadSum = 0.0;

        // For volume-weighted effective spread
        double effectiveSpreadVolumeSum = 0.0;

        // Trade-weighted depth
        double bidSizeSum = 0.0;
        double askSizeSum = 0.0;

        // Trade-weighted order imbalance
        double orderImbalanceSum = 0.0;
    };


    // Key:
    //
    //     symbol + 5-minute timestamp
    //
    // This keeps SPY and QQQ separate if we later
    // aggregate both symbols together.

    using BarKey =
        std::pair<std::string, long long>;

    std::map<BarKey, BarData> buckets;


    // ---------------------------------------------------------
    // Assign every TBBO trade to a 5-minute bucket
    // ---------------------------------------------------------

    for (const TBBOTrade& trade : trades) {

        long long bucketStart =
            (trade.getTimestamp() / FIVE_MINUTES_NS)
            * FIVE_MINUTES_NS;


        BarKey key = {
            trade.getSymbol(),
            bucketStart
        };


        BarData& data = buckets[key];


        // -----------------------------------------------------
        // Basic trade statistics
        // -----------------------------------------------------

        data.tradeCount++;

        data.totalVolume +=
            trade.getSize();

        data.dollarVolume +=
            trade.getNotional();


        // -----------------------------------------------------
        // Quoted spread
        //
        // Trade-weighted:
        // each TBBO observation contributes once.
        // -----------------------------------------------------

        data.quotedSpreadSum +=
            trade.getQuotedSpread();


        // -----------------------------------------------------
        // Effective spread
        //
        // Volume-weighted:
        // larger trades receive more weight.
        // -----------------------------------------------------

        data.effectiveSpreadVolumeSum +=
            trade.getEffectiveSpread()
            * trade.getSize();


        // -----------------------------------------------------
        // Bid / ask depth
        //
        // Trade-weighted averages.
        // -----------------------------------------------------

        data.bidSizeSum +=
            trade.getBidSize();

        data.askSizeSum +=
            trade.getAskSize();


        // -----------------------------------------------------
        // Order imbalance
        //
        // (BidSize - AskSize)
        // -------------------
        // (BidSize + AskSize)
        // -----------------------------------------------------

        double depth =
            static_cast<double>(
                trade.getBidSize()
                + trade.getAskSize()
            );

        if (depth > 0.0) {

            double imbalance =
                static_cast<double>(
                    trade.getBidSize()
                    - trade.getAskSize()
                )
                / depth;

            data.orderImbalanceSum +=
                imbalance;
        }
    }


    // ---------------------------------------------------------
    // Convert accumulated statistics into TBBOBar objects
    // ---------------------------------------------------------

    std::vector<TBBOBar> bars;

    bars.reserve(buckets.size());


    for (const auto& entry : buckets) {

        const BarKey& key =
            entry.first;

        const BarData& data =
            entry.second;


        const std::string& symbol =
            key.first;

        long long startTimestamp =
            key.second;


        // -----------------------------------------------------
        // VWAP
        // -----------------------------------------------------

        double vwap = 0.0;

        if (data.totalVolume > 0) {

            vwap =
                data.dollarVolume
                / static_cast<double>(
                    data.totalVolume
                );
        }


        // -----------------------------------------------------
        // Trade-weighted averages
        // -----------------------------------------------------

        double averageQuotedSpread = 0.0;
        double averageBidSize = 0.0;
        double averageAskSize = 0.0;
        double averageOrderImbalance = 0.0;

        if (data.tradeCount > 0) {

            averageQuotedSpread =
                data.quotedSpreadSum
                / data.tradeCount;

            averageBidSize =
                data.bidSizeSum
                / data.tradeCount;

            averageAskSize =
                data.askSizeSum
                / data.tradeCount;

            averageOrderImbalance =
                data.orderImbalanceSum
                / data.tradeCount;
        }


        // -----------------------------------------------------
        // Volume-weighted effective spread
        // -----------------------------------------------------

        double averageEffectiveSpread = 0.0;

        if (data.totalVolume > 0) {

            averageEffectiveSpread =
                data.effectiveSpreadVolumeSum
                / static_cast<double>(
                    data.totalVolume
                );
        }


        // -----------------------------------------------------
        // Create final TBBOBar
        // -----------------------------------------------------

        bars.emplace_back(
            startTimestamp,
            symbol,
            data.tradeCount,
            data.totalVolume,
            data.dollarVolume,
            vwap,
            averageQuotedSpread,
            averageEffectiveSpread,
            averageBidSize,
            averageAskSize,
            averageOrderImbalance
        );
    }


    return bars;
}