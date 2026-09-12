cmake_minimum_required(VERSION 3.20)

project(odte_market_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
        odte_market_engine
        src/main.cpp
        src/OptionTrade.cpp
)

target_include_directories(
        odte_market_engine
        PRIVATE
        include
)