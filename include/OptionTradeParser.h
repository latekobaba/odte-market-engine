#ifndef OPTION_TRADE_PARSER_H
#define OPTION_TRADE_PARSER_H

#include <string>
#include <vector>

#include "OptionTrade.h"

class OptionTradeParser {
public:
    std::vector<OptionTrade> parseFile(
        const std::string& filePath
    ) const;
};

#endif