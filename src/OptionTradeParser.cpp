#include "OptionTradeParser.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<OptionTrade> OptionTradeParser::parseFile(
    const std::string& filePath
) const
{
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Could not open option trade file."
        );
    }

    std::vector<OptionTrade> trades;

    // Optimization #1:
    // Preallocate capacity to reduce vector reallocations.
    trades.reserve(600000);

    std::string line;

    // Skip the CSV header
    std::getline(file, line);

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        std::string underlyingSymbol;
        std::string marketDate;
        std::string quoteDatetime;
        std::string sequenceNumber;
        std::string root;
        std::string expiration;
        std::string strike;
        std::string optionType;
        std::string exchangeId;
        std::string tradeSize;
        std::string tradePrice;
        std::string tradeConditionId;
        std::string canceledTradeConditionId;
        std::string bestBid;
        std::string bestAsk;
        std::string tradeIv;
        std::string tradeDelta;
        std::string tradeGamma;
        std::string tradeVega;
        std::string tradeTheta;
        std::string tradeRho;
        std::string underlyingBid;
        std::string underlyingAsk;

        std::getline(ss, underlyingSymbol, ',');
        std::getline(ss, marketDate, ',');
        std::getline(ss, quoteDatetime, ',');
        std::getline(ss, sequenceNumber, ',');
        std::getline(ss, root, ',');
        std::getline(ss, expiration, ',');
        std::getline(ss, strike, ',');
        std::getline(ss, optionType, ',');
        std::getline(ss, exchangeId, ',');
        std::getline(ss, tradeSize, ',');
        std::getline(ss, tradePrice, ',');
        std::getline(ss, tradeConditionId, ',');
        std::getline(ss, canceledTradeConditionId, ',');
        std::getline(ss, bestBid, ',');
        std::getline(ss, bestAsk, ',');
        std::getline(ss, tradeIv, ',');
        std::getline(ss, tradeDelta, ',');
        std::getline(ss, tradeGamma, ',');
        std::getline(ss, tradeVega, ',');
        std::getline(ss, tradeTheta, ',');
        std::getline(ss, tradeRho, ',');
        std::getline(ss, underlyingBid, ',');
        std::getline(ss, underlyingAsk, ',');

        // Keep only 0DTE option trades
        if (marketDate != expiration) {
            continue;
        }

        if (underlyingSymbol.empty() ||
            quoteDatetime.empty() ||
            expiration.empty() ||
            strike.empty() ||
            optionType.empty() ||
            tradeSize.empty() ||
            tradePrice.empty() ||
            bestBid.empty() ||
            bestAsk.empty() ||
            tradeIv.empty() ||
            tradeDelta.empty() ||
            tradeGamma.empty() ||
            underlyingBid.empty() ||
            underlyingAsk.empty()) {

            continue;
        }

        try {
            double strikeValue = std::stod(strike);
            char optionTypeValue = optionType[0];

            int sizeValue = std::stoi(tradeSize);
            double priceValue = std::stod(tradePrice);

            double bestBidValue = std::stod(bestBid);
            double bestAskValue = std::stod(bestAsk);

            double ivValue = std::stod(tradeIv);
            double deltaValue = std::stod(tradeDelta);
            double gammaValue = std::stod(tradeGamma);

            double underlyingBidValue = std::stod(underlyingBid);
            double underlyingAskValue = std::stod(underlyingAsk);

            trades.emplace_back(
                quoteDatetime,
                underlyingSymbol,
                expiration,
                strikeValue,
                optionTypeValue,
                priceValue,
                sizeValue,
                bestBidValue,
                bestAskValue,
                ivValue,
                deltaValue,
                gammaValue,
                underlyingBidValue,
                underlyingAskValue
            );
        }
        catch (const std::exception&) {
            continue;
        }
    }

    return trades;
}