#!/bin/bash
# Compile and run without BorrowCommand

g++ -Wall -Wextra -std=c++17 \
Classic.cpp \
Comedy.cpp \
Command.cpp \
Customer.cpp \
Drama.cpp \
Movie.cpp \
MovieStore.cpp \
main.cpp \
store_test.cpp \
-o store_no_borrow

./store_no_borrow