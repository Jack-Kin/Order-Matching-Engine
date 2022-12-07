#pragma once

#include <array>
#include <fstream>
#include <list>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "order.hh"

// typedef std::array<char,16> symbol_t; - not using array of chars for now, will have to define an explicit hash
// function for unordered map if used - MEMORY NOT A CONCERN since it's used only in central order book
typedef std::string symbol_t;

enum StatusCode {
    OK,
    SYMBOL_EXISTS,
    SYMBOL_NOT_EXISTS,
    ORDER_EXISTS,
    ORDER_NOT_EXISTS

};

struct OrderInfo{
    OrderSide side;
    unsigned price;
    OrderType type;
};

class OrderBook{
private:
    unsigned last_buy_price = 0;
    unsigned last_sell_price = std::numeric_limits<unsigned>::max();
    symbol_t company; // also the filename for output
    std::ofstream ostrm;

    std::unordered_map<unsigned, std::list<Order>> buypool, sellpool, stop_buy_orders, stop_sell_orders; // key=price level; value=a list of Order
    // stores current levels of the hashmaps (buypool and sellpool)
    std::set<unsigned, std::less<unsigned>> sellprices, stop_sell_prices;
    std::set<unsigned, std::greater<unsigned>> buyprices, stop_buy_prices;
    std::unordered_map<unsigned, OrderInfo> order_map; // key=order ID, value=(ordertype, price level)

    // std::map is slower than std::unordered_map, see complexity below.
    // std::map<float,std::deque<Order>,std::greater<float>> buypool;
    // std::map<float,std::deque<Order>> sellpool;
    // Adding a map from order id to order object reference since we cannot identify order type just with price level info
	// std::unordered_map<unsigned int, Order&> order_map;

    unsigned get_sell_market_price() const;
    unsigned get_buy_market_price() const;
    void execute_stop_orders();
    template<typename Pred, typename Comp>
    void execute_stop_orders(unsigned, std::set<unsigned, Comp>&, std::unordered_map<unsigned, std::list<Order>>&, Pred);
    void execute_stop_order(Order&, bool);
    void match_order(Order& order);
    void match_order(Order& order, bool isMarket);
    StatusCode add_stop_order(Order&, bool);
    std::optional<OrderInfo> get_order_pair(unsigned int);
    template<typename Comp>
    StatusCode add_to_orderbook(Order& order, unsigned level, std::set<unsigned, Comp>& prices, std::unordered_map<unsigned, std::list<Order>>& pool);
    template<typename Comp>
    void delete_order(unsigned, unsigned, std::set<unsigned, Comp>& prices, std::unordered_map<unsigned, std::list<Order>>& pool);
    void set_last_matching_price(Order& order, unsigned price);

public:
    OrderBook(symbol_t company = "MUDD") :
        company(company),
        ostrm(company, std::ios_base::app)
        {}
    StatusCode add_order(Order&);
    std::optional<Order> get_order(unsigned int);
    StatusCode delete_order(unsigned int);
    unsigned best_ask()const{
        return sellprices.empty() ? std::numeric_limits<unsigned>::max() : *(sellprices.begin()); 
    }
    unsigned best_bid()const{
        return buyprices.empty() ? 0 : *(buyprices.begin());
    }
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
