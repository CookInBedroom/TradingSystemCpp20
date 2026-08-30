add_library(MarketData
        BinanceFeed.h
        BinanceFeed.cpp
)

target_sources(MarketData
        PUBLIC
        BinanceFeed.h
        PRIVATE
        BinanceFeed.cpp
)

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(MarketData
        PUBLIC
            Boost::headers
            nlohmann_json::nlohmann_json
)