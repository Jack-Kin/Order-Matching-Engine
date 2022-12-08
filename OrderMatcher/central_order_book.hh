#include <unordered_map>
#include "orderbook.hh"

/*
    The main Order Book class that maintains the order book for different
    stocks. It provides operations on the order book.
*/
class CentralOrderBook {
    private:
        // map of stock symbol to it's order book
        std::unordered_map<string, OrderBook> order_book_map;
    public:
        
        StatusCode add_symbol(string);
        
        StatusCode add_order(string, Order&);
        
        StatusCode delete_order(string, unsigned int);

        std::optional<Order> get_order(string, unsigned int);

        std::pair<StatusCode, unsigned> best_ask(string) const;

        std::pair<StatusCode, unsigned> best_bid(string) const;

        void printBuySellPool(string) const;
};