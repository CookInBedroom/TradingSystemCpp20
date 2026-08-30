//
// Created by alexl on 8/17/2026.
//

#include "BinanceFeed.h"

#include <iostream>
#include <boost/beast/core.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace ssl = asio::ssl;

using bf = md::BinanceFeed;
using tcp = asio::ip::tcp;
using json = nlohmann::json;

bf::BinanceFeed() = default;

void bf::run() {
    // jthread for the websocket loop
    asio::io_context ioc;


    // json order book snapshot
    OrderBookSnapshot snapshot = fetch_order_book_snapshot();
}

bf::OrderBookSnapshot bf::fetch_order_book_snapshot() {
    std::cout << "[REST] Sending order book snapshot request..." << std::endl;

    OrderBookSnapshot snapshot;

    cpr::Response response = cpr::Get(
        cpr::Url{"https://binance.com/api/v3/depth"},
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

    try {
        // parse response text that is natively in the json format
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

// 1
// CPU Cache Line Bouncing for ring buffer queue
// If head and tail sit next to each other in memory,
// the two CPU cores will constantly invalidate each other's cache lines
// (False Sharing). In production code, you must separate them using alignas(64).

// 2  memory order semantics for ring buffer queue (search it)

// 3 index changes in a ring buffer
// If your size N is a power of 2 (like 1024 or 4096),
// you can use a much faster bitwise AND (index & (N - 1)) instead of modulo.

// 4 One stop_source controls MULTIPLE threads
//std::stop_source ssource;

//std::jthread t1(sensor_loop, ssource.get_token(), "Sensor-A");
//std::jthread t2(sensor_loop, ssource.get_token(), "Sensor-B");
//std::jthread t3(sensor_loop, ssource.get_token(), "Sensor-C");

//
