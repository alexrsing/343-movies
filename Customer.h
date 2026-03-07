#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <utility>
#include <vector>

#include "Movie.h"

class Customer;

// Factory class for creating Customer objects from input data
class CustomerFactory {
public:
  static Customer *makeCustomer(std::string data);
};

// Represents a customer of the movie rental store.
// Each customer has a unique ID, a name, and a transaction history.
class Customer {
public:
  // Constructor initializes customer attributes
  Customer(int id, std::string firstName, std::string lastName)
      : id(id), firstName(firstName), lastName(lastName) {};

  // Static factory instance for creating Customer objects from input data
  static CustomerFactory factory;

  // Returns the customer's ID
  int getID() const;

  // Adds a transaction to the customer's history
  void addTransaction(char key, Movie *movie);

  // Returns the customer's transaction history
  std::vector<std::pair<char, Movie *>> getTransactions() const;

  // Prints the customer's transaction history
  void printTransactions() const;

  // Checks if the customer has currently borrowed the given movie
  bool hasBorrowed(Movie *movie) const;

private:
  // Customer attributes
  int id;
  std::string firstName;
  std::string lastName;

  // Transaction history: vector of pairs of (transaction type, movie pointer)
  std::vector<std::pair<char, Movie *>> transactions;
};

#endif