#ifndef BINANCEFEED_H
#define BINANCEFEED_H

#include <vector>

namespace md {
    struct OrderBookSnapshot {
        long long last_update_id;
        std::vector<std::pair<double, double>> bids;
        std::vector<std::pair<double, double>> asks;
    };

    class BinanceFeed {
    public:
        BinanceFeed();
        static void run();

    // private:
        static OrderBookSnapshot fetch_order_book_snapshot();
    };
}

#endif
