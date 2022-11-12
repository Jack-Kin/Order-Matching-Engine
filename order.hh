#pragma once
#include <array>
#include <chrono>

enum class OrderType : char {
    limit,
    market,
    stop,
    stop_limit
};

class Order{
private:
    unsigned short order_id;
    unsigned short quantity; 
    unsigned quote;
    OrderType order_type;
    char is_buy; // buy=1, sell=0
    char all_or_none; // aon=1, partial order allowed=0
    std::chrono::time_point<std::chrono::system_clock> timestamp;
public:
    Order(unsigned short id, unsigned short qty, unsigned quote, OrderType tp, char buy, char aon, std::chrono::time_point<std::chrono::system_clock> tmstmp):
        order_id(id),
        quantity(qty),
        quote(quote),
        order_type(tp),
        is_buy(buy),
        all_or_none(aon),
        timestamp(tmstmp){}
    auto get_id()const{return order_id;}
    auto get_quantity()const{return quantity;}
    void reduce_quantity(unsigned short x){quantity-=x;} 
    auto get_quote()const{return quote;}
    auto get_type()const{return order_type;}
    auto isBuy()const{return is_buy;}
    auto isAON()const{return all_or_none;}
    auto get_time()const{return timestamp;}
};

class Transaction{
public:
    unsigned short buyside_order_id;
    unsigned short sellside_order_id;
    unsigned final_price; // price at which a transaction was done
    unsigned short quantity; // In case of partial order
    std::chrono::time_point<std::chrono::system_clock> timestamp; // when the transaction was completed; -- not sure if useful
};