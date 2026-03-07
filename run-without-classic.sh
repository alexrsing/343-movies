#!/bin/bash
# Compile and run without Classic genre

g++ -Wall -Wextra -std=c++17 \
BorrowCommand.cpp \
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
-o store_no_classic

./store_no_classic
