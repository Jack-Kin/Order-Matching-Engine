#pragma once
// #include <queue>
#include <deque>
#include <limits>
#include <map>
#include <unordered_map>

#include "order.hh"
#include <optional>

class OrderBook{
private:
    std::map<float,std::deque<Order>,std::greater<float>> buypool;
    std::map<float,std::deque<Order>> sellpool;
    // If orders in a level are deleted, we cannot delete it from the priority queue
    // Hence reverting to map for buy/sell pool, we can revise data structure in v 1.0
	// std::priority_queue<float> buyprices;
    // std::priority_queue<float, vector<float>, std::greater<float>> sellprices;
    // Adding a map from order id to order object reference since we cannot identify order type just with price level info
	std::unordered_map<unsigned int, Order&> order_map;
    void add_market_order(Order&);
    void add_limit_order(Order&);
public:
    void add_order(Order&);
    std::optional<Order> get_order(unsigned int);
    bool delete_order(unsigned int);
    void printBuySellPool();
};

/*Complexity:

n = no of orders
Add order: 
Add to buy/sellpool - O(log n) 
Add to order_map - O(1)

Delete order: 
delete from buy/sell pool -O(log n)
delete from order map - O(1)
*/
