#pragma once
#include <queue>

#include "order.hh"

struct Comp{ // Counterpart of std::less
    constexpr bool operator()(const Order &a, const Order &b)const{
        return a.quote_price<b.quote_price || \
            (a.quote_price==b.quote_price&&a.timestamp<b.timestamp);
    }
};

class OrderBook{
private:
    std::priority_queue<Order, std::vector<Order>, Comp> buypool, sellpool; // maxheap: highest buy price, lowest sell price
    std::vector<CompletedOrder> match();
public:
    int add_order(Order);
    int view_order(); //?
};