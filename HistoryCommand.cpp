#include "HistoryCommand.h"
#include "MovieStore.h"
#include <iostream>
#include <sstream>

// Registers the History command with the MovieStore
static bool registered = [] {
  MovieStore::registerCommandFactory('H', new HistoryCommandFactory());
  return true;
}();

// Default constructor for HistoryCommandFactory
HistoryCommandFactory::HistoryCommandFactory() {}

// Creates a HistoryCommand from input command data
Command *HistoryCommandFactory::createCommand(std::string data,
                                              MovieStore *store) const {
  // Parse data from input string into HistoryCommand constructor parameters
  // Skip command type character at start of line
  if (data.length() < 2) {
    std::cout << "Invalid history command data: " << data << std::endl;
    return nullptr;
  }
  std::istringstream iss(data.substr(2));
  int customerID;

  iss >> customerID;

  // Use store parameter to look up movie and customer
  Customer *customer = store->getCustomer(customerID);
  if (customer == nullptr) {
    std::cout << "Customer " << customerID << " not found" << std::endl;
    return nullptr;
  }

  return new HistoryCommand(store, customer);
}

// Executes the history command and prints customer transactions
void HistoryCommand::execute() {
  // Check that customer is valid --- this should not be necessary
  if (customer == nullptr) {
    std::cout << "Customer not found" << std::endl;
    return;
  }

  // Print this customers transaction history
  customer->printTransactions();
}