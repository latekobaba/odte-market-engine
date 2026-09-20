#include "OptionBarAggregator.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>


std::vector<OptionBar> OptionBarAggregator::aggregate(
    const std::vector<OptionTrade>& trades
) const {

    // ---------------------------------------------------------
    // Running statistics for one 5-minute bucket
    // ---------------------------------------------------------

    struct BucketData {

        int tradeCount = 0;

        int totalVolume = 0;
        int callVolume = 0;
        int putVolume = 0;

        double totalNotional = 0.0;
        double priceVolume = 0.0;

        double totalSpread = 0.0;
        double totalIV = 0.0;
        double totalDelta = 0.0;
        double totalGamma = 0.0;
        double totalATMDistance = 0.0;
    };


    // ---------------------------------------------------------
    // Key:
    //
    //     symbol + 5-minute timestamp
    //
    // Example:
    //
    //     SPY | 2023-01-03 09:30
    //
    // We keep the pair structure, but use an unordered_map
    // instead of std::map.
    // ---------------------------------------------------------

    using BucketKey =
        std::pair<std::string, std::string>;


    // ---------------------------------------------------------
    // Custom hash function for:
    //
    //     pair<string, string>
    //
    // std::unordered_map needs a way to convert the pair
    // into a hash value.
    // ---------------------------------------------------------

    struct BucketKeyHash {

        std::size_t operator()(
            const BucketKey& key
        ) const noexcept {

            std::size_t symbolHash =
                std::hash<std::string>{}(
                    key.first
                );


            std::size_t timestampHash =
                std::hash<std::string>{}(
                    key.second
                );


            return symbolHash ^
                   (
                       timestampHash +
                       0x9e3779b9 +
                       (symbolHash << 6) +
                       (symbolHash >> 2)
                   );
        }
    };


    std::unordered_map<
        BucketKey,
        BucketData,
        BucketKeyHash
    > buckets;


    // ---------------------------------------------------------
    // We expect only a relatively small number of final bars
    // compared with the number of trades.
    //
    // Reserving space reduces rehashing while the map grows.
    // ---------------------------------------------------------

    buckets.reserve(256);


    // ---------------------------------------------------------
    // Single pass through all option trades
    // ---------------------------------------------------------

    for (const OptionTrade& trade : trades) {

        const std::string& timestamp =
            trade.getTimestamp();


        // -----------------------------------------------------
        // Read the minute directly from the timestamp.
        //
        // Example:
        //
        // 2023-01-03 09:58:35.587
        //               ^^
        //
        // minute = 58
        // -----------------------------------------------------

        int minute =
            (timestamp[14] - '0') * 10 +
            (timestamp[15] - '0');


        int bucketMinute =
            (minute / 5) * 5;


        // -----------------------------------------------------
        // Construct YYYY-MM-DD HH:MM directly.
        // -----------------------------------------------------

        std::string bucketTimestamp =
            timestamp.substr(0, 14);


        bucketTimestamp +=
            static_cast<char>(
                '0' + bucketMinute / 10
            );


        bucketTimestamp +=
            static_cast<char>(
                '0' + bucketMinute % 10
            );


        BucketKey key{
            trade.getSymbol(),
            bucketTimestamp
        };


        // -----------------------------------------------------
        // Hash-table lookup rather than tree lookup.
        // -----------------------------------------------------

        BucketData& bucket =
            buckets[key];


        // -----------------------------------------------------
        // Accumulate statistics directly
        // -----------------------------------------------------

        ++bucket.tradeCount;


        int size =
            trade.getSize();


        bucket.totalVolume +=
            size;


        bucket.totalNotional +=
            trade.getNotional();


        bucket.priceVolume +=
            trade.getPrice() * size;


        bucket.totalSpread +=
            trade.getBestAsk() -
            trade.getBestBid();


        bucket.totalIV +=
            trade.getImpliedVolatility();


        bucket.totalDelta +=
            trade.getDelta();


        bucket.totalGamma +=
            trade.getGamma();


        bucket.totalATMDistance +=
            std::abs(
                trade.getMoneyness() - 1.0
            );


        if (trade.getOptionType() == 'C') {

            bucket.callVolume +=
                size;
        }
        else if (trade.getOptionType() == 'P') {

            bucket.putVolume +=
                size;
        }
    }


    // ---------------------------------------------------------
    // unordered_map does NOT preserve the sorted order that
    // std::map gave us.
    //
    // Create bars first, then sort them by:
    //
    //     symbol
    //     timestamp
    //
    // This preserves the externally visible ordering of the
    // previous implementation.
    // ---------------------------------------------------------

    std::vector<OptionBar> bars;


    bars.reserve(
        buckets.size()
    );


    for (const auto& [key, bucket] : buckets) {

        const std::string& symbol =
            key.first;


        const std::string& bucketTimestamp =
            key.second;


        double vwap = 0.0;


        if (bucket.totalVolume > 0) {

            vwap =
                bucket.priceVolume /
                bucket.totalVolume;
        }


        double averageSpread = 0.0;
        double averageIV = 0.0;
        double averageDelta = 0.0;
        double averageGamma = 0.0;
        double averageATMDistance = 0.0;


        if (bucket.tradeCount > 0) {

            averageSpread =
                bucket.totalSpread /
                bucket.tradeCount;


            averageIV =
                bucket.totalIV /
                bucket.tradeCount;


            averageDelta =
                bucket.totalDelta /
                bucket.tradeCount;


            averageGamma =
                bucket.totalGamma /
                bucket.tradeCount;


            averageATMDistance =
                bucket.totalATMDistance /
                bucket.tradeCount;
        }


        bars.emplace_back(
            bucketTimestamp,
            symbol,
            bucket.tradeCount,
            bucket.totalVolume,
            bucket.totalNotional,
            bucket.callVolume,
            bucket.putVolume,
            vwap,
            averageSpread,
            averageIV,
            averageDelta,
            averageGamma,
            averageATMDistance
        );
    }


    // ---------------------------------------------------------
    // Restore deterministic ordering:
    //
    // QQQ before SPY, and timestamps ascending within symbol.
    //
    // This matches the ordering produced by the previous
    // std::map<pair<string,string>, ...> implementation.
    // ---------------------------------------------------------

    std::sort(
        bars.begin(),
        bars.end(),
        [](
            const OptionBar& a,
            const OptionBar& b
        ) {

            if (a.getSymbol() != b.getSymbol()) {

                return a.getSymbol() <
                       b.getSymbol();
            }


            return a.getStartTimestamp() <
                   b.getStartTimestamp();
        }
    );


    return bars;
}