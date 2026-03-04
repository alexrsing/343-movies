#!/bin/bash
# Compile and run without Drama genre

g++ -Wall -Wextra -std=c++17 \
BorrowCommand.cpp \
Classic.cpp \
Comedy.cpp \
Command.cpp \
Customer.cpp \
Movie.cpp \
MovieStore.cpp \
main.cpp \
store_test.cpp \
-o store_no_drama

./store_no_drama