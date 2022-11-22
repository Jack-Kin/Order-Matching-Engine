#include "orderbook.hh"

int main(){

    OrderBook book;

    Order buy1(1,2,1000,15,OrderSide::BUY,OrderType::LIMIT,0);
    Order buy2(2,2,800,5,OrderSide::BUY,OrderType::LIMIT,0);
    Order buy3(3,2,600,5,OrderSide::BUY,OrderType::LIMIT,0);
    Order sell1(4,2,1000,5,OrderSide::SELL,OrderType::LIMIT,0);
    Order sell2(5,2,800,15,OrderSide::SELL,OrderType::LIMIT,0);
    Order sell3(6,2,600,5,OrderSide::SELL,OrderType::LIMIT,0);

    book.add_order(buy1);
    book.add_order(buy2);
    book.add_order(buy3);
    book.printBuySellPool();
    book.add_order(sell1);
    book.printBuySellPool();
    book.add_order(sell2);
    book.add_order(sell3);

    book.printBuySellPool();
    // // std::cout << "fetch order 1 " << book.get_order(1) << std::endl;
    // book.delete_order(6);
    // book.delete_order(1);
    // book.delete_order(10); // shouldn't delete
    // book.printBuySellPool();

    return 0;
}