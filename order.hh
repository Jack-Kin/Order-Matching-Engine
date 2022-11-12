#pragma once
#include <array>
#include <chrono>
#include <iostream>

enum class OrderSide {
    BUY,
    SELL
};

enum class OrderType {
    MARKET,
    LIMIT
};

class Order{
    friend std::ostream& operator<<(std::ostream &s, const Order &order);
    public:
        unsigned int order_id;
        std::array<char,16> owner;
        OrderSide order_side;
        OrderType order_type;
        float price;
        unsigned short int quantity; 
        char all_or_none; // Reserved, char used as bool
        std::chrono::time_point<std::chrono::system_clock> timestamp;
        Order(unsigned int order_id, std::array<char,16> owner,char order_side, char order_type, float price, unsigned short int qty, char all_or_none, std::chrono::system_clock::time_point time){
            this->owner = owner;
            //change next 2 lines based on parser output
            this->order_side = order_side == 'B' ? OrderSide :: BUY : OrderSide :: SELL;
            this->order_type = order_type == 'M' ? OrderType :: MARKET : OrderType :: LIMIT;
            this->price = price;
            this-> quantity = qty;
            this->timestamp = time;
            this->all_or_none = all_or_none;
            //this->order_id = boost::lexical_cast<std::string>(generator());
            this->order_id = order_id;
        }
        auto get_id()const{return order_id;}
        auto get_quantity()const{return quantity;}
        void reduce_quantity(unsigned short x){quantity-=x;} 
        auto get_quote()const{return price;}
        auto get_type()const{return order_type;}
        auto isBuy()const{return order_side == OrderSide :: BUY;}
        auto isAON()const{return all_or_none;}
        auto get_time()const{return timestamp;}
};

std::ostream& operator<<(std::ostream &s, const Order &order) {
    return s << "(" << order.order_id << ", "
    << ", " << static_cast<std::underlying_type<OrderSide>::type>(order.order_side) << ", " 
    << static_cast<std::underlying_type<OrderType>::type>(order.order_type)
    << ", " << order.price << ", " << order.quantity ;
}


class Transaction{
public:
    unsigned short buyside_order_id;
    unsigned short sellside_order_id;
    unsigned final_price; // price at which a transaction was done
    unsigned short quantity; // In case of partial order
    std::chrono::time_point<std::chrono::system_clock> timestamp; // when the transaction was completed; -- not sure if useful
};
