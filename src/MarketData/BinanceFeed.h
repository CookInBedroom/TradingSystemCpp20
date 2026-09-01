//
// Created by alexl on 8/17/2026.
//

#ifndef BINANCEFEED_H
#define BINANCEFEED_H

#include <vector>

namespace md {
    class BinanceFeed {
    public:
        BinanceFeed();
        void run();

    // private:
        struct OrderBookSnapshot {
            long long last_update_id;
            std::vector<std::pair<double, double>> bids;
            std::vector<std::pair<double, double>> asks;
        };

        static OrderBookSnapshot fetch_order_book_snapshot();
    };
}

#endif
