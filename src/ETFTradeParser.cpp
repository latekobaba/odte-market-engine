

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
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        std::string timestampStr;
        std::string symbol;
        std::string priceStr;
        std::string sizeStr;
        std::string sideStr;
        std::string sequenceStr;

        // Read all six fields first
        std::getline(ss, timestampStr, ',');
        std::getline(ss, symbol, ',');
        std::getline(ss, priceStr, ',');
        std::getline(ss, sizeStr, ',');
        std::getline(ss, sideStr, ',');
        std::getline(ss, sequenceStr);

        // Make sure none of the six fields is empty
        if (timestampStr.empty() ||
            symbol.empty() ||
            priceStr.empty() ||
            sizeStr.empty() ||
            sideStr.empty() ||
            sequenceStr.empty()) {

            continue;
            }

        try {
            long long timestamp = std::stoll(timestampStr);
            double price = std::stod(priceStr);
            int size = std::stoi(sizeStr);
            char side = sideStr[0];
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
        catch (const std::exception&) {
            continue;
        }
    }
    return trades;
}
