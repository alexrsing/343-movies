#!/bin/bash
# Compile and run without BorrowCommand

g++ -Wall -Wextra -std=c++17 \
Classic.cpp \
Comedy.cpp \
Customer.cpp \
Drama.cpp \
HistoryCommand.cpp \
InventoryCommand.cpp \
Movie.cpp \
MovieStore.cpp \
ReturnCommand.cpp \
main.cpp \
store_test.cpp \
-o store_no_borrow

./store_no_borrow
