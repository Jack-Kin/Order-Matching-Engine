cmake_minimum_required(VERSION 3.16)
project(Order_Matching_Engine)

set(CMAKE_CXX_STANDARD 20)

#add_executable(Order_Matching_Engine main.cpp)

add_executable(Order_Test order_test.cc order.cc order.hh)

add_executable(Order_Book_Test orderbook_test.cc
        order.cc order.hh
        orderbook.cc orderbook.hh
        central_order_book.cc central_order_book.hh
        ordermatching.cc)
