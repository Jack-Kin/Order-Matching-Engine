#pragma once
#include <array>
#include <chrono>

class Order{
public:
    unsigned short order_id;
    std::array<char,16> company;
    float price;
    short quantity; // positive=buy, negative=sell
    char all_or_none; // Reserved, char used as bool
    std::chrono::time_point<std::chrono::system_clock> timestamp;
};