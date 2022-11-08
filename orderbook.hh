#pragma once
#include <queue>

#include "order.hh"

struct Comp{
    constexpr bool operator()(const Order &a, const Order &b)const{
        return a.price<b.price || (a.price==b.price&&a.timestamp<b.timestamp);
    }
};

class OrderBook{
private:
    std::priority_queue<Order, std::vector<Order>, Comp> buypool, sellpool;

public:
    int add_order(Order);
};