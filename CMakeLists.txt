cmake_minimum_required(VERSION 4.3)
project(TradingSystemCpp20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src/MarketData)

add_executable(TradingSystemCpp20 main.cpp)
target_link_libraries(TradingSystemCpp20 PRIVATE MarketData)
