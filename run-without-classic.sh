#!/bin/bash
# Compile and run without Classic genre

g++ -Wall -Wextra -std=c++17 \
BorrowCommand.cpp \
Comedy.cpp \
Command.cpp \
Customer.cpp \
Drama.cpp \
Movie.cpp \
MovieStore.cpp \
main.cpp \
store_test.cpp \
-o store_no_classic

./store_no_classic