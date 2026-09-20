cmake_minimum_required(VERSION 3.20)

project(odte_market_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()


# ============================================================
# Main 0DTE Market Engine
# ============================================================

add_executable(
        odte_market_engine
        src/main.cpp
        src/OptionTrade.cpp
        src/ETFTrade.cpp
        src/ETFTradeParser.cpp
        src/MarketDataEngine.cpp
        include/ETFBar.h
        src/ETFBar.cpp
        include/ETFBarAggregator.h
        src/ETFBarAggregator.cpp
        include/OptionTradeParser.h
        src/OptionTradeParser.cpp
        include/OptionBar.h
        src/OptionBar.cpp
        include/OptionBarAggregator.h
        src/OptionBarAggregator.cpp
        include/MarketBar.h
        src/MarketBar.cpp
        include/MarketBarAggregator.h
        src/MarketBarAggregator.cpp
        include/TBBOTrade.h
        src/TBBOTrade.cpp
        include/TBBOTradeParser.h
        src/TBBOTradeParser.cpp
        include/TBBOBar.h
        src/TBBOBar.cpp
        include/TBBOBarAggregator.h
        src/TBBOBarAggregator.cpp
)

target_include_directories(
        odte_market_engine
        PRIVATE
        include
)




# ============================================================
# Tests
# ============================================================

# ------------------------------------------------------------
# OptionTrade Test
# ------------------------------------------------------------

add_executable(
        test_option_trade
        tests/test_option_trade.cpp
        src/OptionTrade.cpp
)

target_include_directories(
        test_option_trade
        PRIVATE
        include
)


# ------------------------------------------------------------
# OptionBarAggregator Test
# ------------------------------------------------------------

add_executable(
        test_option_bar_aggregator
        tests/test_option_bar_aggregator.cpp
        src/OptionTrade.cpp
        src/OptionBar.cpp
        src/OptionBarAggregator.cpp
        tests/test_market_integration.cpp
)

target_include_directories(
        test_option_bar_aggregator
        PRIVATE
        include
)


# ------------------------------------------------------------
# TBBOTrade Test
# ------------------------------------------------------------

add_executable(
        test_tbbo_trade
        tests/test_tbbo_trade.cpp
        src/TBBOTrade.cpp
)

target_include_directories(
        test_tbbo_trade
        PRIVATE
        include
)


# ------------------------------------------------------------
# TBBOBarAggregator Test
# ------------------------------------------------------------

add_executable(
        test_tbbo_bar_aggregator
        tests/test_tbbo_bar_aggregator.cpp
        src/TBBOTrade.cpp
        src/TBBOBar.cpp
        src/TBBOBarAggregator.cpp
)

target_include_directories(
        test_tbbo_bar_aggregator
        PRIVATE
        include
)

# ============================================================
# Market Integration Test
# ============================================================

add_executable(
        test_market_integration
        tests/test_market_integration.cpp
        src/TBBOTrade.cpp
        src/TBBOBar.cpp
        src/TBBOBarAggregator.cpp
        src/OptionTrade.cpp
        src/OptionBar.cpp
        src/OptionBarAggregator.cpp
)

target_include_directories(
        test_market_integration
        PRIVATE
        include
)

# ============================================================
# CTest Registration
# ============================================================

add_test(
        NAME OptionTradeTest
        COMMAND test_option_trade
)

add_test(
        NAME OptionBarAggregatorTest
        COMMAND test_option_bar_aggregator
)

add_test(
        NAME TBBOTradeTest
        COMMAND test_tbbo_trade
)

add_test(
        NAME TBBOBarAggregatorTest
        COMMAND test_tbbo_bar_aggregator
)

add_test(
        NAME MarketIntegrationTest
        COMMAND test_market_integration
)