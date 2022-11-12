#pragma once
#include <array>
#include <chrono>

enum class OrderType : char {
    limit,
    market,
    stop,
    stop_limit
};

class Order{
public:
    unsigned short order_id;
    unsigned short quantity; 
    unsigned quote;
    OrderType order_type;
    char is_buy; // buy=1, sell=0
    char all_or_none; // aon=1, partial order allowed=0
    std::chrono::time_point<std::chrono::system_clock> timestamp;
};

class Transaction{
public:
    unsigned short buyside_order_id;
    unsigned short sellside_order_id;
    unsigned final_price; // price at which a transaction was done
    unsigned short quantity; // In case of partial order
    std::chrono::time_point<std::chrono::system_clock> timestamp; // when the transaction was completed; -- not sure if useful
}