#include "HistoryCommand.h"
#include <sstream>

// Factory constructor
HistoryCommandFactory::HistoryCommandFactory() {}

Command *HistoryCommandFactory::createCommand(std::string data,
                                              MovieStore *store) const {
  // parse data from input string into BorrowCommand constructor parameters
  std::istringstream iss(data);
  int customerID;
  std::string mediaType;
  char movieType;

  iss >> customerID >> mediaType >> movieType;

  // Capture the remaining movie-identifying data
  std::string movieData;
  std::getline(iss, movieData);

  // Use store parameter to look up movie and customer
  Customer *customer = store->getCustomer(customerID);
  if (customer == nullptr) {
    std::cout << "Customer " << customerID << " not found" << std::endl;
    return nullptr;
  }

  for (Movie *movie : store->getMovies(movieType)) {
    // if this is the correct movie, return a new BorrowCommand object
    if (movie->isEqual(movieData)) {
      return new HistoryCommand(store, customer, movie);
    }
  }

  // data does not match customer or movie
  std::cout << "Invalid history command data: " << data << std::endl;
  return nullptr;
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