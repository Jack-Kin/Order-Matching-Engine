#pragma once
#include <list>
#include <queue>
#include <unordered_map>

#include "order.hh"

// struct Comp{ // Counterpart of std::less
//     constexpr bool operator()(const Order &a, const Order &b)const{
//         return a.quote<b.quote || \
//             (a.quote==b.quote&&a.timestamp<b.timestamp);
//     }
// };

class OrderBook{
private:
    std::array<char,16> company;
    std::unordered_map<unsigned, std::list<Order>> buypool, sellpool; // key=price level; value=a list of Order
    std::priority_queue<unsigned> buyprices, sellprices; // stores current levels of the hashmaps (buypool and sellpool)
    std::unordered_map<unsigned, unsigned> priceofID; // key=order ID, value=price level
    std::vector<Transaction> match_limit(Order &order);
    std::vector<Transaction> match_market(Order &order);
public:
    int add_order(Order &order);
    int view_order();
    int remove_order(unsigned order_id);
};