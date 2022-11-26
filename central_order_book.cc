#include "central_order_book.hh"

StatusCode CentralOrderBook::add_symbol(symbol_t symbol, unsigned price){
    StatusCode status;
    if (order_book_map.count(symbol) != 0){
        status = StatusCode :: SYMBOL_EXISTS;
    } else{
        order_book_map[symbol] = OrderBook(price);
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

void CentralOrderBook::printBuySellPool(symbol_t symbol)const{
    order_book_map.at(symbol).printBuySellPool();
}