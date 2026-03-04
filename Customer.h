#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Movie.h"

class Customer;

class CustomerFactory {
public:
  static Customer *makeCustomer(std::string data);
};

class Customer {
public:
  Customer(int id, std::string firstName, std::string lastName)
      : id(id), firstName(firstName), lastName(lastName) {};

  static CustomerFactory factory;
  int getID() const;

  void addTransaction(char key, Movie *movie);
  std::unordered_map<char, std::vector<Movie *>> getTransactions() const;
  void printTransactions() const;

private:
  int id;
  std::string firstName;
  std::string lastName;
  std::unordered_map<char, std::vector<Movie *>> transaction;
};

#endif