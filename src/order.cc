#include "order.hh"

std::ostream& operator<<(std::ostream &s, const OrderSide side) {
    if (side == OrderSide::BUY){
        s << "BUY";
    }else{
        s << "SELL";
    }
    return s;
}

std::ostream& operator<<(std::ostream &s, const OrderType type) {
    switch(type){
        case OrderType::LIMIT:
         s << "LIMIT";
         break;
        case OrderType::MARKET:
         s << "MARKET";
         break;
    }
    return s;
}

std::ostream& operator<<(std::ostream &s, const Order &order) {
        return s << "(Id = " << order.order_id << ", Owner = " << order.owner_id
        << ", Side = " << order.order_side << ", Type = " << order.order_type
        << ", Quote = " << order.quote << ", Qty = " << order.quantity << "\n";
}