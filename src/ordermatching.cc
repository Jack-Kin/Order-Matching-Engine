#include "orderbook.hh"

// private:
std::vector<Transaction> OrderBook::match_order(Order& order){
    std::cout << "In match\n" ;
    std::vector<Transaction> result;
    bool isbuy = order.get_side()==OrderSide::BUY;
    while(!(isbuy ? sellprices.empty() : buyprices.empty())){
        auto level = isbuy ? best_ask() : best_bid();
        if(isbuy ? order.get_quote() < level : order.get_quote() > level){
            return result;
        }
        if(order.isAON()){
            // to be completed in ver 1.0. Line 1225
            return result;
        }
        auto & nowlist = isbuy ? sellpool[level] : buypool[level];
        while(!nowlist.empty()){
            auto & noworder = nowlist.front();
            auto quantity = std::min(noworder.get_quantity(), order.get_quantity());
            if(noworder.isAON() && noworder.get_quantity() > order.get_quantity()){
                return result;
            }
            
            // execute the order
            result.push_back(Transaction(isbuy?order.get_id():noworder.get_id(), isbuy?noworder.get_id():order.get_id(), level, quantity));
            noworder.reduce_quantity(quantity);
            //update matching price
            set_last_matching_price(noworder, level);
            if(noworder.get_quantity()==0){
                order_map.erase(noworder.get_id());
                nowlist.pop_front();
                if(nowlist.empty()){
                    if(isbuy){
                        sellpool.erase(level);
                        sellprices.erase(level);
                    }else{
                        buypool.erase(level);
                        buyprices.erase(level);
                    }
                }
            }
            order.reduce_quantity(quantity);
            if(order.get_quantity()==0){
                // need to delete this entry from pool similar to noworder
                return result;
            }
        }
    }
    //activate stop orders
    return result;
}


std::vector<Transaction> OrderBook::match_order(Order& order, bool isMarket){
    // Made minor change of passing boolean to prevent repeating same code in multiple places
    if(isMarket){
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
    }
    auto res = match_order(order);
    return res;
}