#include "orderbook.hh"

int main(){

    OrderBook book;
    unsigned int order_id = 1;
    std::array<char,16> owner = {"ABC"};
    double price = 1000.0;
    // uint32_t qty = 5;
    Order buy1(1,2,1000,5,OrderSide::BUY,OrderType::MARKET,' ',std::chrono::system_clock::now());
    Order buy2(2,2,800,15,OrderSide::BUY,OrderType::MARKET,' ',std::chrono::system_clock::now());
    Order buy3(3,2,600,5,OrderSide::BUY,OrderType::LIMIT,' ',std::chrono::system_clock::now());
    // Order buy2(2,2,'B','M',800.0,10,' ',std::chrono::system_clock::now());
    // Order buy3(3,2,'B','L',600.0,5,' ',std::chrono::system_clock::now());
    Order sell1(4,2,1000,5,OrderSide::SELL,OrderType::MARKET,' ',std::chrono::system_clock::now());
    Order sell2(5,2,800,15,OrderSide::SELL,OrderType::LIMIT,' ',std::chrono::system_clock::now());
    Order sell3(6,2,600,5,OrderSide::SELL,OrderType::LIMIT,' ',std::chrono::system_clock::now());
    // Order sell1(4,owner,'S','M',1000.0,5,' ',std::chrono::system_clock::now());
    // Order sell2(5,owner,'S','L',800.0,10,' ',std::chrono::system_clock::now());
    // Order sell3(6,owner,'S','L',600.0,5,' ',std::chrono::system_clock::now());
    // // Order buy2("2","ABC",'B',800.0,5,std::chrono::system_clock::now());
    // // Order buy3("3","ABC",'B',900.0,5,std::chrono::system_clock::now());
    book.add_order(buy1);
    book.add_order(buy2);
    book.add_order(buy3);

    book.add_order(sell1);
    book.add_order(sell2);
    book.add_order(sell3);

    book.printBuySellPool();
    // std::cout << "fetch order 1 " << book.get_order(1) << std::endl;
    book.delete_order(6);
    book.delete_order(1);
    book.delete_order(10); // shouldn't delete
    book.printBuySellPool();

    return 0;
}