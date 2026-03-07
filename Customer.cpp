#include "Customer.h"

#include <sstream>
#include <vector>

// Static factory instance for creating Customer objects from input data
CustomerFactory Customer::factory;

// Parses a line of customer data and creates a Customer object
Customer *CustomerFactory::makeCustomer(std::string data) {
  // parse data and set customer fields
  int id;
  std::string firstName;
  std::string lastName;

  std::istringstream iss(data);
  iss >> id >> lastName >> firstName;

  return new Customer(id, firstName, lastName);
}

// Returns the customer's ID
int Customer::getID() const { return this->id; }

// Returns the customer's first name
std::string Customer::getFirstName() const { return this->firstName; }

// Returns the customer's last name
std::string Customer::getLastName() const { return this->lastName; }

// Adds a transaction to the customer's history
void Customer::addTransaction(char key, Movie *movie) {
  transactions.emplace_back(key, movie);
}

// Returns the customer's transaction history
std::vector<std::pair<char, Movie *>> Customer::getTransactions() const {
  return transactions;
}

// Checks if the customer has currently borrowed the given movie
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

// Prints the customer's transaction history
void Customer::printTransactions() const {
  std::cout << "History for " << id << " " << lastName << " " << firstName
            << ":" << std::endl;

  if (transactions.empty()) {
    std::cout << "No history for " << lastName << " " << firstName << std::endl;
    return;
  }

  for (const auto &t : transactions) {
    std::string action = (t.first == 'B') ? "Borrow" : "Return";
    std::cout << action << " " << lastName << " " << firstName << " "
              << t.second->getTitle() << std::endl;
  }
}