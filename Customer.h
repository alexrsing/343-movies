#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <utility>
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
  std::vector<std::pair<char, Movie *>> getTransactions() const;
  void printTransactions() const;
  bool hasBorrowed(Movie *movie) const;

private:
  int id;
  std::string firstName;
  std::string lastName;
  std::vector<std::pair<char, Movie *>> transactions;
};

#endif