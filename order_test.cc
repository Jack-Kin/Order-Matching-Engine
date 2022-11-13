#include "order.hh"

int main(){
    auto t = std::chrono::system_clock::now();
    Order od(1,1,1,OrderType::LIMIT,1,1,t);
    std::cout << od.get_id() << "\n";
    return 0;
}