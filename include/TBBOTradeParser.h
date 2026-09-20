#ifndef TBBOTRADEPARSER_H
#define TBBOTRADEPARSER_H

#include "TBBOTrade.h"

#include <string>
#include <vector>

class TBBOTradeParser {
public:
    std::vector<TBBOTrade> parseCSV(const std::string& filePath,
                                    const std::string& symbol) const;
};

#endif