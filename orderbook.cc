#include "orderbook.hh"

// private:

void OrderBook::add_limit_order(Order& order){
    if(order.get_side() == OrderSide ::BUY){
        // if (buypool.find(order.get_quote()) == buypool.end()){ //price level not found
        //     buyprices.push(order.get_quote());
        // }
        buypool[order.get_quote()].push_back(order);
    } else{
        // if (sellpool.find(order.get_quote()) == sellpool.end()){ //price level not found
        //     sellprices.push(order.get_quote());
        // }
        sellpool[order.get_quote()].push_back(order); 
    }
    order_map.insert({order.order_id,order});
}


void OrderBook::add_market_order(Order& order){
    if(order.get_side() == OrderSide ::BUY){
        //check top of sellprices for best sell price, if not exists set to max
        order.set_quote(std::numeric_limits<float>::max());
        buypool[order.get_quote()].push_back(order);
    } else{
        order.set_quote(0.0);
        sellpool[order.get_quote()].push_back(order); 
    }
    order_map.insert({order.order_id,order});
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
    auto order = order_map.find(order_id);
    if (order == order_map.end()){ 
        return {};
    }
    return order->second;
}


bool OrderBook::delete_order(unsigned int order_id){
    //find order in price map
    auto order_obj = get_order(order_id);
    if (!order_obj){
        return false;
    }
    Order order = *order_obj;
    order_map.erase(order_id);
    // check buypool and delete from list
    std::list<Order> order_list;
    if(order.get_side() == OrderSide ::BUY){
        order_list = buypool[order.get_quote()]; // this is just a copy (also taking a lot of time)
        for (auto it = order_list.begin(); it != order_list.end(); ++it) {
        if(it->order_id == order_id){
            order_list.erase(it); // deleted the object in the copy, but not in the original one.
            if(order_list.empty()){ 
                buypool.erase(order.get_quote()); 
            }
            return true;
        }
    }   
    }else{
        order_list = sellpool[order.get_quote()];
        for (auto it = order_list.begin(); it != order_list.end(); ++it) {
        if(it->order_id == order_id){
            order_list.erase(it);
            if(order_list.empty()){ 
                sellpool.erase(order.get_quote());
            }
            return true;
        }
    }
    }
    return false;  
}


void OrderBook::printBuySellPool()const{
    std::cout << "BuyPool" << "\n";
    for (auto const &pair: buypool) {
        std::cout << "{" << pair.first << "}\n";
        for (auto it = pair.second.begin(); it != pair.second.end(); ++it)
            std::cout << ' ' << *it << "}\n";
    }

    std::cout << "SellPool" << "\n";
    for (auto const &pair: sellpool) {
        std::cout << "{" << pair.first << "}\n";
        for (auto it = pair.second.begin(); it != pair.second.end(); ++it)
            std::cout << ' ' << *it << "}\n";
    }
}
