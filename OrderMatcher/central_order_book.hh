#include <unordered_map>
#include "orderbook.hh"

/*
    The main Order Book class that maintains the order book for different
    stocks. It provides operations on the order book.
*/
class CentralOrderBook {
    private:
        // map of stock symbol to it's order book
        std::unordered_map<std::string, OrderBook> order_book_map;
        const char* SymbolFilter[4] =
            { "AAPL", "MSFT", "TSLA", "AMZN"};
    // store a hash map of orderID to symbols

public:
        
        StatusCode add_symbol(std::string);
        
        StatusCode add_order(std::string, Order&);
        
        StatusCode delete_order(std::string, unsigned int);

        std::optional<Order> get_order(std::string, unsigned int);

        std::pair<StatusCode, unsigned> best_ask(std::string) const;

        std::pair<StatusCode, unsigned> best_bid(std::string) const;

        void printBuySellPool(std::string) const;
};