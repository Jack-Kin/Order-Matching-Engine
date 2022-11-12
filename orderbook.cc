#include "orderbook.hh"


void OrderBook::add_order(Order& order){
    switch(order.order_type){
        case OrderType :: MARKET:
            add_market_order(order);
            break;
        case OrderType :: LIMIT:
            add_limit_order(order);
            break;
    }
}

void OrderBook::add_limit_order(Order& order){
    if(order.order_side == OrderSide ::BUY){
        // if (buypool.find(order.price) == buypool.end()){ //price level not found
        //     buyprices.push(order.price);
        // }
        buypool[order.price].push_back(order);
    } else{
        // if (sellpool.find(order.price) == sellpool.end()){ //price level not found
        //     sellprices.push(order.price);
        // }
        sellpool[order.price].push_back(order); 
    }
    order_map.insert({order.order_id,order});
}

void OrderBook::add_market_order(Order& order){
    if(order.order_side == OrderSide ::BUY){
        //check top of sellprices for best sell price, if not exists set to max
        order.price = std::numeric_limits<float>::max();
        buypool[order.price].push_back(order);
    } else{
        order.price = 0.0;
        sellpool[order.price].push_back(order); 
    }
    order_map.insert({order.order_id,order});
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
    // check buypool and delete from deque
    std::deque<Order> order_list;
    if(order.order_side == OrderSide ::BUY){
        order_list = buypool[order.price];
        for (auto it = order_list.begin(); it != order_list.end(); ++it) {
        if(it->order_id == order_id){
            order_list.erase(it);
            if(order_list.empty()){ 
                buypool.erase(order.price);
            }
            return true;
        }
    }   
    }else{
        order_list = sellpool[order.price];
        for (auto it = order_list.begin(); it != order_list.end(); ++it) {
        if(it->order_id == order_id){
            order_list.erase(it);
            if(order_list.empty()){ 
                sellpool.erase(order.price);
            }
            return true;
        }
    }
    }
    return false;  
}

void OrderBook::printBuySellPool()
{
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

// std::vector<Transaction> OrderBook::match_market(Order &order){
    
// }

int main(){

    OrderBook book;
    unsigned int order_id = 1;
    std::array<char,16> owner = {"ABC"};
    double price = 1000.0;
    // uint32_t qty = 5;
    Order buy1(1,owner,'B','M',1000.0,5,' ',std::chrono::system_clock::now());
    Order buy2(2,owner,'B','M',800.0,10,' ',std::chrono::system_clock::now());
    Order buy3(3,owner,'B','L',600.0,5,' ',std::chrono::system_clock::now());

    Order sell1(4,owner,'S','M',1000.0,5,' ',std::chrono::system_clock::now());
    Order sell2(5,owner,'S','L',800.0,10,' ',std::chrono::system_clock::now());
    Order sell3(6,owner,'S','L',600.0,5,' ',std::chrono::system_clock::now());
    // Order buy2("2","ABC",'B',800.0,5,std::chrono::system_clock::now());
    // Order buy3("3","ABC",'B',900.0,5,std::chrono::system_clock::now());
    book.add_order(buy1);
    book.add_order(buy2);
    book.add_order(buy3);

    book.add_order(sell1);
    book.add_order(sell2);
    book.add_order(sell3);

    book.printBuySellPool();
    // std::cout << "fetch order 1 " << book.get_order(1) << std::endl;
    book.delete_order(6);
    book.delete_order(10); // shouldn't delete
    book.printBuySellPool();
}