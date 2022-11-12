#pragma once

#include <chrono>
#include <ostream>

enum class OrderSide : unsigned char{
    BUY,
    SELL,
    SELL_SHORT,
    SELL_SHORT_EXEMPT,
    CROSS,
    CROSS_SHORT,
    CROSS_SHORT_EXEMPT
};

enum class OrderType : unsigned char {
    LIMIT,
    MARKET,
    STOP,
    STOP_LIMIT
};

class Order{
private:
    unsigned order_id;
    unsigned owner_id;
    unsigned quantity; 
    unsigned quote;
    OrderSide order_side;
    OrderType order_type;
    char all_or_none; // aon=1, partial order allowed=0
    std::chrono::time_point<std::chrono::system_clock> timestamp;
public:
    Order(unsigned order, unsigned owner, unsigned qty, unsigned quote, OrderSide sd, OrderType tp, char aon, std::chrono::time_point<std::chrono::system_clock> tmstmp):
        order_id(order),
        owner_id(owner),
        quantity(qty),
        quote(quote),
        order_side(sd),
        order_type(tp),
        all_or_none(aon),
        timestamp(tmstmp){}
    auto get_id()const{return order_id;}
    auto get_owner()const{return owner_id;}
    auto get_quantity()const{return quantity;}
    void reduce_quantity(unsigned x){quantity-=x;} // only if aon=0
    auto get_quote()const{return quote;}
    void set_quote(unsigned x){quote=x;} // only for market orders
    auto get_side()const{return order_side;}
    auto get_type()const{return order_type;}
    auto isAON()const{return all_or_none;}
    auto get_time()const{return timestamp;}
};

std::ostream& operator<<(std::ostream &s, const Order &order) {
    return s << "(" << order.get_id() << ", "
    << ", " << static_cast<std::underlying_type<OrderSide>::type>(order.get_side()) << ", " 
    << static_cast<std::underlying_type<OrderType>::type>(order.get_type())
    << ", " << order.get_quote() << ", " << order.get_quantity() << "\n";
}

class Transaction{
public:
    unsigned buyside_order_id;
    unsigned sellside_order_id;
    unsigned final_price; // price at which a transaction was done
    unsigned quantity; // In case of partial order
    std::chrono::time_point<std::chrono::system_clock> timestamp; // when the transaction was completed; -- not sure if useful
};
