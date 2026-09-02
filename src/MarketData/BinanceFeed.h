#ifndef BINANCEFEED_H
#define BINANCEFEED_H

#include <vector>
#include <cstdint>

namespace md {
    struct OrderBookSnapshot {
        std::int64_t last_update_id;
        std::vector<std::pair<double, double>> bids;
        std::vector<std::pair<double, double>> asks;
    };

    class BinanceFeed {
    public:
        BinanceFeed();
        void run();

    // private:
        OrderBookSnapshot fetch_order_book_snapshot();
    };
}

#endif
