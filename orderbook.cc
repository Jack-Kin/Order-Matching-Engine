#include "orderbook.hh"

// private:

void OrderBook::add_limit_order(Order& order){
    if(order.get_side() == OrderSide ::BUY){
        if (buypool.find(order.get_quote()) == buypool.end()){ //price level not found
            buyprices.insert(order.get_quote());
        }
        buypool[order.get_quote()].push_back(order);
    } else{
        if (sellpool.find(order.get_quote()) == sellpool.end()){ //price level not found
            sellprices.insert(order.get_quote());
        }
        sellpool[order.get_quote()].push_back(order); 
    }
    order_map.insert({order.get_id(),std::make_pair(order.get_side(),order.get_quote())});
}


void OrderBook::add_market_order(Order& order){
    if(order.get_side() == OrderSide ::BUY){
        //check top of sellprices for best sell price, if not exists set to max
        order.set_quote(std::numeric_limits<unsigned>::max());
        if (buypool.find(order.get_quote()) == buypool.end()){ //price level not found
            buyprices.insert(order.get_quote());
        }
        buypool[order.get_quote()].push_back(order);
    } else{
        order.set_quote(0.0);
        if (sellpool.find(order.get_quote()) == sellpool.end()){ //price level not found
            sellprices.insert(order.get_quote());
        }
        sellpool[order.get_quote()].push_back(order); 
    }
    order_map.insert({order.get_id(),std::make_pair(order.get_side(),order.get_quote())});
}

std::optional<std::pair<OrderSide,unsigned>> OrderBook::get_order_helper(unsigned int order_id){
    //check order map
    auto order = order_map.find(order_id);
    if (order == order_map.end()){ 
        return {};
    }
    return order->second;
}


// public:

void OrderBook::add_order(Order& order){
    switch(order.get_type()){
        case OrderType :: MARKET:
            add_market_order(order);
            break;
        case OrderType :: LIMIT:
            add_limit_order(order);
            break;
    }
}


std::optional<Order> OrderBook::get_order(unsigned int order_id){
    //check order map
    auto order_details = get_order_helper(order_id);
    if (!order_details){
        return {};
    }
    auto order_pair = *order_details;
    OrderSide side = order_pair.first;
    unsigned price = order_pair.second;
    std::list<Order> order_list;
    if(side == OrderSide ::BUY){
        order_list = buypool[price];
    }else{
        order_list = sellpool[price];
    }
    for (auto it = order_list.begin(); it != order_list.end(); ++it) {
        if(it->get_id() == order_id){
            return *it;
        }
    }
    return {};
}


bool OrderBook::delete_order(unsigned int order_id){
    //find order in price map
    //todo: code requires a bit of cleaning
    auto order_details = get_order_helper(order_id);
    if (!order_details){
        return false;
    }
    auto order_pair = *order_details;
    order_map.erase(order_id);
    // check buypool and delete from list
    if(order_pair.first == OrderSide ::BUY){
        for (auto it = buypool[order_pair.second].begin(); it != buypool[order_pair.second].end(); ++it) {
        if(it->get_id() == order_id){
            buypool[order_pair.second].erase(it); // deleted the object in the copy, but not in the original one.
            if(buypool[order_pair.second].empty()){ 
                buypool.erase(order_pair.second);
                buyprices.erase(order_pair.second);  
            }
            return true;
        }
    }   
    }else{
        for (auto it = sellpool[order_pair.second].begin(); it != sellpool[order_pair.second].end(); ++it) {
        if(it->get_id() == order_id){
            sellpool[order_pair.second].erase(it);
            if(sellpool[order_pair.second].empty()){ 
                sellpool.erase(order_pair.second);
                sellprices.erase(order_pair.second);  
            }
            return true;
        }
    }
    }
    return false;  
}


void OrderBook::printBuySellPool()const{
    std::cout << "BuyPool" << "\n";
    for (auto const& price : buyprices)
    {
        std::cout << price << ' ';
    }
    for (auto const &pair: buypool) {
        std::cout << "{" << pair.first << "}\n";
        for (auto it = pair.second.begin(); it != pair.second.end(); ++it)
            std::cout << ' ' << *it << "}\n";
    }

    std::cout << "SellPool" << "\n";
    for (auto const& price : sellprices)
    {
        std::cout << price << ' ';
    }
    for (auto const &pair: sellpool) {
        std::cout << "{" << pair.first << "}\n";
        for (auto it = pair.second.begin(); it != pair.second.end(); ++it)
            std::cout << ' ' << *it << "}\n";
    }
}
