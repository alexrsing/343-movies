#include "Customer.h"

#include <sstream>
#include <vector>

CustomerFactory Customer::factory;

Customer *CustomerFactory::makeCustomer(std::string data) {
  // parse data and set customer fields
  int id;
  std::string firstName;
  std::string lastName;

  std::istringstream iss(data);
  iss >> id >> firstName >> lastName;

  return new Customer(id, firstName, lastName);
}

int Customer::getID() const {
  //
  return this->id;
}

void Customer::addTransaction(char key, Movie *movie) {
  transaction[key].push_back(movie);
}

std::unordered_map<char, std::vector<Movie *>>
Customer::getTransactions() const {
  return transaction;
}

void Customer::printTransactions() const {
  std::cout << "Transaction history for " << firstName << " " << lastName
            << " (ID: " << id << "):" << std::endl;

  for (const auto &entry : transaction) {
    std::string action = (entry.first == 'B') ? "Borrowed" : "Returned";
    for (Movie *movie : entry.second) {
      std::cout << "  - " << action << ": ";
      movie->print();
    }
  }
}