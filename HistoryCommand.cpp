#include "HistoryCommand.h"
#include <iostream>
#include <sstream>

// Factory constructor
HistoryCommandFactory::HistoryCommandFactory() {}

Command *HistoryCommandFactory::createCommand(std::string data,
                                              MovieStore *store) const {
  // parse data from input string into BorrowCommand constructor parameters
  std::istringstream iss(data);
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

void HistoryCommand::execute() {
  // check that customer is valid --- this should not be necessary
  if (customer == nullptr) {
    std::cout << "Customer not found" << std::endl;
    return;
  }

  // print this customers transaction history
  customer->printTransactions();
}