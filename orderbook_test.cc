#include "central_order_book.hh"

int main(){

    
    CentralOrderBook book;

    symbol_t s1 = "APPLE";
    book.add_symbol(s1);

    Order buy1(1,2,1000,15,OrderSide::BUY,OrderType::LIMIT,0);
    Order buy2(2,2,800,5,OrderSide::BUY,OrderType::LIMIT,0);
    Order buy3(3,2,600,5,OrderSide::BUY,OrderType::LIMIT,0);
    Order sell1(4,2,1000,5,OrderSide::SELL,OrderType::LIMIT,0);
    Order sell2(5,2,800,15,OrderSide::SELL,OrderType::LIMIT,0);
    Order sell3(6,2,600,5,OrderSide::SELL,OrderType::LIMIT,0);

    book.add_order(s1,buy1);
    book.add_order(s1,buy2);
    book.add_order(s1,buy3);
    book.printBuySellPool(s1);
    book.add_order(s1,sell1);
    book.printBuySellPool(s1);
    book.add_order(s1,sell2);
    book.add_order(s1,sell3);

    book.printBuySellPool(s1);
    // // std::cout << "fetch order 1 " << book.get_order(1) << std::endl;
    Order buy4(1,2,1000,15,OrderSide::BUY,OrderType::LIMIT,0);
    book.add_order(s1,buy4);
    book.printBuySellPool(s1);
    book.delete_order(s1,6);
    book.delete_order(s1,1);
    // book.delete_order(10); // shouldn't delete
    book.printBuySellPool(s1);

    return 0;
}