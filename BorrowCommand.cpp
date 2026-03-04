#include "BorrowCommand.h"
#include "MovieStore.h"
#include <iostream>
#include <sstream>

// Factory constructor
BorrowCommandFactory::BorrowCommandFactory() {}

Command *BorrowCommandFactory::createCommand(std::string data,
                                             MovieStore *store) const {
  // parse data from input string into BorrowCommand constructor parameters
  // skip command type character at start of line
  if (data.length() < 2) {
    std::cout << "Invalid borrow command data: " << data << std::endl;
    return nullptr;
  }
  std::istringstream iss(data.substr(2));
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
      return new BorrowCommand(store, customer, movie);
    }
  }

  // data does not match customer or movie
  std::cout << "Invalid borrow command data: " << data << std::endl;
  return nullptr;
}

void BorrowCommand::execute() {
  MovieStore *store = getStore();

  // the following checks should not be necessary if createCommand is
  // implemented correctly
  // check customer is valid
  if (customer == nullptr) {
    std::cout << "Customer not found" << std::endl;
    return;
  }

  // check movie is valid
  if (movie == nullptr) {
    std::cout << "Movie not found" << std::endl;
    return;
  }

  if (store->borrowMovie(customer, movie)) {
    customer->addTransaction('B', movie);
    return;
  }

  std::cout << "Movie not available for borrowing" << std::endl;
}