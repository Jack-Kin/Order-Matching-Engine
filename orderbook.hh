#pragma once

#include <array>
#include <list>
#include <optional>
#include <set>
#include <unordered_map>
#include <vector>

#include "order.hh"

class OrderBook{
private:
    std::array<char,16> symbol;
    std::unordered_map<unsigned, std::list<Order>> buypool, sellpool; // key=price level; value=a list of Order
    std::set<unsigned> buyprices, sellprices; // stores current levels of the hashmaps (buypool and sellpool)
    std::unordered_map<unsigned, std::pair<OrderSide,unsigned>> order_map; // key=order ID, value=(ordertype, price level)

    // std::map is slower than std::unordered_map, see complexity below.
    // std::map<float,std::deque<Order>,std::greater<float>> buypool;
    // std::map<float,std::deque<Order>> sellpool;
    // Adding a map from order id to order object reference since we cannot identify order type just with price level info
	// std::unordered_map<unsigned int, Order&> order_map;

    auto best_ask()const{return *(sellprices.begin());}
    auto best_bid()const{return *(buyprices.rbegin());}
    std::vector<Transaction> match_order(Order& order);
    auto match_limit(Order& order){return match_order(order);}
    std::vector<Transaction> match_market(Order& order);
    Order& add_limit_order(Order&);
    Order& add_market_order(Order&);
    std::optional<std::pair<OrderSide,unsigned>> get_order_pair(unsigned int);

public:
    void add_order(Order&);
    std::optional<Order> get_order(unsigned int);
    bool delete_order(unsigned int);
    void printBuySellPool()const;
};

/*Complexity:
N orders; M orders per price

Add order: 
Add to buy/sellpool - average O(M); O(M + log N) if using std::map
// Add to order_map - O(1)

Delete order: 
delete from buy/sell pool - average O(M); O(log N) ? if using order_map
// delete from order map - O(1)
*/
