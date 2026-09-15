

#ifndef ETF_TRADE_PARSER_H
#define ETF_TRADE_PARSER_H

#include <string>
#include <vector>
#include "ETFTrade.h"


class ETFTradeParser {
public:
    std::vector<ETFTrade> parseFile(const std::string& filePath);
};




#endif // ETF_TRADE_PARSER_H
