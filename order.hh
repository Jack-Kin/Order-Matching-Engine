#pragma once
#include <array>
#include <chrono>

class Order{
public:
    unsigned short order_id;
    std::array<char,16> company;
    float quote_price; // positive=buy, negative=sell
    short quantity; 
    char all_or_none; // Reserved, char used as bool
    std::chrono::time_point<std::chrono::system_clock> timestamp;
};

class CompletedOrder{
public:
    unsigned short order_id;
    float final_price; // price at which a transaction was done
    short quantity; // In case of partial order
    std::chrono::time_point<std::chrono::system_clock> timestamp; // when the transaction was completed; -- not sure if usefull
}