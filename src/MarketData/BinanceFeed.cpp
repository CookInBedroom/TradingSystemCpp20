#include "BinanceFeed.h"

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace md {
    BinanceFeed::BinanceFeed() = default;

    void BinanceFeed::run() {
        // jthread for the websocket loop
        // asio::io_context ioc;

        OrderBookSnapshot snapshot = fetch_order_book_snapshot();
    }

    /// Fetches an initial state of BTCUSDT order book from Binance's OrderbookSnapshot REST endpoint.
    OrderBookSnapshot BinanceFeed::fetch_order_book_snapshot() {
        std::cout << "[REST] Sending order book snapshot request..." << std::endl;

        OrderBookSnapshot snapshot {};

        cpr::Response response = cpr::Get(
            cpr::Url{"https://api.binance.com/api/v3/depth"},
            cpr::Parameters{
                {"symbol", "BTCUSDT"},
                {"limit", "20"} // top 20 records
            },
            cpr::Timeout{4000} // 4-second timeout threshold
        );

        if (response.status_code != 200) {
            std::cerr << "[Error] Failed REST call with response status code: " << response.status_code << std::endl;
            return snapshot;
        }

        /* Parse the JSON response and store in a snapshot struct */
        try {
            json json_response = json::parse(response.text);

            snapshot.last_update_id = json_response.at("lastUpdateId").get<long long>();

            for (const json& bid_entry : json_response.at("bids")) {
                double price = std::stod(bid_entry[0].get<std::string>());
                double quantity = std::stod(bid_entry[1].get<std::string>());
                snapshot.bids.emplace_back(price, quantity);
            }

            for (const json& ask_entry : json_response.at("asks")) {
                double price = std::stod(ask_entry[0].get<std::string>());
                double quantity = std::stod(ask_entry[1].get<std::string>());
                snapshot.asks.emplace_back(price, quantity);
            }
        }
        catch (const json::exception& e) {
            std::cerr << "[Error] Failed to parse order book snapshot: " << e.what() << std::endl;
        }

        return snapshot;
    }

}
