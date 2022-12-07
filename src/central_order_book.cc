#include "central_order_book.hh"

StatusCode CentralOrderBook::add_symbol(symbol_t symbol){
    StatusCode status;
    if (order_book_map.count(symbol) != 0){
        status = StatusCode :: SYMBOL_EXISTS;
    } else{
        order_book_map[symbol] = OrderBook();
        status = StatusCode :: OK;
    }
    return status;
}

StatusCode CentralOrderBook::add_order(symbol_t symbol, Order& order){
    StatusCode status;
    auto order_book_ptr = order_book_map.find(symbol);
    
    if (order_book_ptr == order_book_map.end()){
        status = StatusCode :: SYMBOL_NOT_EXISTS;
        // std::cout << "symbol not found";
    } else{
        // std::cout << "symbol found";
        (order_book_ptr->second).add_order(order);
        status = StatusCode :: OK;
    }
    return status;
}

std::optional<Order> CentralOrderBook::get_order(symbol_t symbol, unsigned int order_id){
    auto order_book_ptr = order_book_map.find(symbol);
    
    if (order_book_ptr == order_book_map.end()){
        return {};
    }
    return (order_book_ptr->second).get_order(order_id);
}

StatusCode CentralOrderBook::delete_order(symbol_t symbol, unsigned int order_id){
    StatusCode status;
    auto order_book_ptr = order_book_map.find(symbol);
    if (order_book_ptr == order_book_map.end()){
        status = StatusCode :: SYMBOL_NOT_EXISTS;
    } else{
        (order_book_ptr->second).delete_order(order_id);
        status = StatusCode :: OK;
    }
    return status;
}

std::pair<StatusCode, unsigned> CentralOrderBook::best_ask(symbol_t symbol) const{
    StatusCode status;
    unsigned price = std::numeric_limits<unsigned>::max();
    auto order_book_ptr = order_book_map.find(symbol);
    if (order_book_ptr == order_book_map.end()){
        status = StatusCode :: SYMBOL_NOT_EXISTS;
    } else{
        price = (order_book_ptr->second).best_ask();
        status = StatusCode :: OK;
    }
    return std::make_pair(status, price);
}

std::pair<StatusCode, unsigned> CentralOrderBook::best_bid(symbol_t symbol) const{
    StatusCode status;
    unsigned price = 0;
    auto order_book_ptr = order_book_map.find(symbol);
    if (order_book_ptr == order_book_map.end()){
        status = StatusCode :: SYMBOL_NOT_EXISTS;
    } else{
        price = (order_book_ptr->second).best_bid();
        status = StatusCode :: OK;
    }
    return std::make_pair(status, price);
}

void CentralOrderBook::printBuySellPool(symbol_t symbol)const{
    order_book_map.at(symbol).printBuySellPool();
}