#pragma once
#include <queue>

#include "order.hh"

struct Comp{ // Counterpart of std::less
    constexpr bool operator()(const Order &a, const Order &b)const{
        return a.price<b.price || (a.price==b.price&&a.timestamp<b.timestamp);
    }
};

class OrderBook{
private:
    std::priority_queue<Order, std::vector<Order>, Comp> buypool, sellpool; // maxheap: highest buy price, lowest sell price

public:
    int add_order(Order);
};