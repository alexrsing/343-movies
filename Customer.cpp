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
  transactions.emplace_back(key, movie);
}

std::vector<std::pair<char, Movie *>> Customer::getTransactions() const {
  return transactions;
}

bool Customer::hasBorrowed(Movie *movie) const {
  int borrowCount = 0;
  for (const auto &t : transactions) {
    if (t.second == movie) {
      if (t.first == 'B') {
        borrowCount++;
      } else if (t.first == 'R') {
        borrowCount--;
      }
    }
  }
  return borrowCount > 0;
}

void Customer::printTransactions() const {
  std::cout << "Transaction history for " << firstName << " " << lastName
            << " (ID: " << id << "):" << std::endl;

  for (const auto &t : transactions) {
    std::string action = (t.first == 'B') ? "Borrowed" : "Returned";
    std::cout << "  - " << action << ": ";
    t.second->print();
  }
}