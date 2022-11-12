#include "orderbook.hh"

std::vector<CompletedOrder> OrderBook::match(){
    while(!buypool.empty()&&!sellpool.empty()&&buypool.top().quote_price+sellpool.top().quote_price>0){
        
    }
}

int OrderBook::add_order(Order order){
    
}