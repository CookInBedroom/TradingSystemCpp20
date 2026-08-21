add_library(MarketData
        BinanceWebSocket.h
        BinanceWebSocket.cpp
)

target_sources(MarketData
        PUBLIC
            BinanceWebSocket.h
        PRIVATE
            BinanceWebSocket.cpp
)

find_package(Boost REQUIRED)

target_link_libraries(MarketData
        PUBLIC
            Boost::headers
)