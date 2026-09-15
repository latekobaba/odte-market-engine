

#include "ETFTradeParser.h"

#include <fstream>
#include <stdexcept>
#include <sstream>

std::vector<ETFTrade> ETFTradeParser::parseFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open ETF trade file.");
    }

    std::vector<ETFTrade> trades;
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        std::string timestampStr;
        std::getline(ss, timestampStr, ',');
        long long timestamp = std::stoll(timestampStr);

        std::string symbol;
        std::getline(ss, symbol, ',');

        std::string priceStr;
        std::getline(ss, priceStr, ',');
        double price = std::stod(priceStr);

        std::string sizeStr;
        std::getline(ss, sizeStr, ',');
        int size = std::stoi(sizeStr);

        std::string sideStr;
        std::getline(ss, sideStr, ',');
        char side = sideStr[0];

        std::string sequenceStr;
        std::getline(ss, sequenceStr);
        long long sequence = std::stoll(sequenceStr);

        trades.emplace_back(
            timestamp,
            symbol,
            price,
            size,
            side,
            sequence
        );
    }


    return trades;
}