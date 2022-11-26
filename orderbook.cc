#include "orderbook.hh"

// private:

StatusCode OrderBook::add_to_orderbook(Order& order){
    unsigned order_id = order.get_id();
    if(order_map.count(order_id) != 0){
        return StatusCode :: ORDER_EXISTS;
    }
    unsigned quote = order.get_quote();
    OrderSide side = order.get_side();
    bool isbuy = side==OrderSide::BUY;
    std::unordered_map<unsigned, std::list<Order>>& pool = isbuy ? buypool : sellpool;
    std::set<unsigned>& prices = isbuy ? buyprices : sellprices;
    if (pool.find(quote) == pool.end()){ //price level not found
            prices.insert(quote);
    }
    pool[quote].push_back(order);
    order_map.insert({order.get_id(),std::make_pair(side, quote)});
    return StatusCode :: OK;
}


// Order& OrderBook::add_market_order(Order& order){
//     OrderSide side = order.get_side();
//     unsigned quote = (side==OrderSide::BUY) ? std::numeric_limits<unsigned>::max() : 0.0;
//     order.set_quote(quote);
//     return add_limit_order(order);
// }

std::optional<std::pair<OrderSide,unsigned>> OrderBook::get_order_pair(unsigned int order_id){
    //check order map
    auto order = order_map.find(order_id);
    if (order == order_map.end()){ 
        return {};
    }
    return order->second;
}


// public:

StatusCode OrderBook::add_order(Order& order){
    StatusCode status = StatusCode :: OK;
    switch(order.get_type()){
        case OrderType :: MARKET:
            match_market(order);  
            break;
        case OrderType :: LIMIT:
            match_limit(order);
            break;
    }
    if (order.get_quantity() > 0){
        // std::cout << "Order qty " << order.get_quantity();
        status = add_to_orderbook(order);
    }
    return status; 
}


std::optional<Order> OrderBook::get_order(unsigned int order_id){
    //check order map
    auto order_details = get_order_pair(order_id);
    if (!order_details){
        return {};
    }
    auto order_pair = *order_details;
    OrderSide side = order_pair.first;
    unsigned price = order_pair.second;
    std::list<Order>& order_list = (side == OrderSide ::BUY) ? buypool[price] : sellpool[price];
    for (auto it = order_list.begin(); it != order_list.end(); ++it) {
        if(it->get_id() == order_id){
            return *it;
        }
    }
    return {};
}


StatusCode OrderBook::delete_order(unsigned int order_id){
    auto order_details = get_order_pair(order_id);
    if (!order_details){
        return StatusCode :: ORDER_NOT_EXISTS;
    }
    auto order_pair = *order_details;
    order_map.erase(order_id);
    unsigned price = order_pair.second;
    bool isbuy = order_pair.first==OrderSide::BUY;
    std::unordered_map<unsigned, std::list<Order>>& pool = isbuy ? buypool : sellpool;
    std::set<unsigned>& prices = isbuy ? buyprices : sellprices;
    // check buypool and delete from list
    for (auto it = pool[price].begin(); it != pool[price].end(); ++it) {
        if(it->get_id() == order_id){
            pool[price].erase(it);
            if(pool[price].empty()){ 
                // std::cout << "Del from pool \n";
                pool.erase(price);
                prices.erase(price);  
            }
            break;;
        }
    }
    return StatusCode :: OK;  
}


void OrderBook::printBuySellPool()const{
    std::cout << "BuyPrices are:" << "\n";
    for (auto const& price : buyprices)
    {
        std::cout << price << ' ';
    }
    std::cout << "\nBuyPool" << "\n";
    for (auto const &pair: buypool) {
        std::cout << "{" << pair.first << "}\n";
        for (auto it = pair.second.begin(); it != pair.second.end(); ++it)
            std::cout << ' ' << *it <<"}\n";
    }
    std::cout << "SellPrices are:" << "\n";
    for (auto const& price : sellprices)
    {
        std::cout << price << ' ';
    }
    std::cout << "\nSellPool" << "\n";
    for (auto const &pair: sellpool) {
        std::cout << "{" << pair.first << "}\n";
        for (auto it = pair.second.begin(); it != pair.second.end(); ++it)
            std::cout << ' ' << *it << "}\n";
    }
}
