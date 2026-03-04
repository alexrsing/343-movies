#!/bin/bash
# Compile and run without Comedy genre

g++ -Wall -Wextra -std=c++17 \
BorrowCommand.cpp \
Classic.cpp \
Command.cpp \
Customer.cpp \
Drama.cpp \
Movie.cpp \
MovieStore.cpp \
main.cpp \
store_test.cpp \
-o store_no_comedy

./store_no_comedy