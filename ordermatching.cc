#include "orderbook.hh"

// private:
std::vector<Transaction> OrderBook::match_order(Order &order){
    
}


std::vector<Transaction> OrderBook::match_market(Order &order){
    if(order.get_side()==OrderSide::BUY){
        if(sellprices.empty()){
            return {};
        }
        order.set_quote(best_ask());
    }else if(order.get_side()==OrderSide::SELL){
        if(buyprices.empty()){
            return {};
        }
        order.set_quote(best_bid());
    }
    return match_order(order);
}