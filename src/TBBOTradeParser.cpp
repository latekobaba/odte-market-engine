#include "TBBOTradeParser.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<TBBOTrade> TBBOTradeParser::parseCSV(
        const std::string& filePath,
        const std::string& symbol) const {

    std::vector<TBBOTrade> trades;

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Could not open TBBO file: "
                  << filePath << '\n';
        return trades;
    }

    std::string line;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string field;

        try {
            // ts_event
            std::getline(ss, field, ',');
            long long timestamp = std::stoll(field);

            // price
            std::getline(ss, field, ',');
            double price = std::stod(field);

            // size
            std::getline(ss, field, ',');
            int size = std::stoi(field);

            // side
            std::getline(ss, field, ',');
            char side = field.at(0);

            // bid_px_00
            std::getline(ss, field, ',');
            double bidPrice = std::stod(field);

            // ask_px_00
            std::getline(ss, field, ',');
            double askPrice = std::stod(field);

            // bid_sz_00
            std::getline(ss, field, ',');
            int bidSize = std::stoi(field);

            // ask_sz_00
            std::getline(ss, field, ',');
            int askSize = std::stoi(field);

            trades.emplace_back(
                timestamp,
                symbol,
                price,
                size,
                side,
                bidPrice,
                askPrice,
                bidSize,
                askSize
            );
        }
        catch (const std::exception&) {
            // Skip malformed rows
            continue;
        }
    }

    return trades;
}