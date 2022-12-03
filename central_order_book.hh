#include <unordered_map>
#include "orderbook.hh"

class CentralOrderBook {
    private:
        std::unordered_map<symbol_t, OrderBook> order_book_map;
    public:
        //add symbol
        StatusCode add_symbol(symbol_t);
        //add order
        StatusCode add_order(symbol_t, Order&);
        //delete order
        StatusCode delete_order(symbol_t, unsigned int);

        void printBuySellPool(symbol_t) const;
};