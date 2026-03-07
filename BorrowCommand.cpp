#include "BorrowCommand.h"
#include "MovieStore.h"
#include <iostream>
#include <sstream>

// Registers the Borrow command factory with the MovieStore
static bool registered = [] {
  MovieStore::registerCommandFactory('B', new BorrowCommandFactory());
  return true;
}();

// Constructor for BorrowCommandFactory
BorrowCommandFactory::BorrowCommandFactory() {}

// Creates a BorrowCommand from a line of command input
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

  // Validate media type
  if (!store->validMediaType(mediaType[0])) {
    std::cout << "Invalid media type " << mediaType
              << ", discarding line: " << movieData << std::endl;
    return nullptr;
  }

  // Validate movie type
  if (store->getMovies(movieType).empty()) {
    std::cout << "Invalid movie type " << movieType
              << ", discarding line: " << movieData << std::endl;
    return nullptr;
  }

  // Use store parameter to look up movie and customer
  Customer *customer = store->getCustomer(customerID);
  if (customer == nullptr) {
    std::cout << "Invalid customer ID " << customerID << ", discarding line: "
              << " " << mediaType << " " << movieType << movieData << std::endl;
    return nullptr;
  }

  for (Movie *movie : store->getMovies(movieType)) {
    // if this is the correct movie, return a new BorrowCommand object
    if (movie->isEqual(movieData)) {
      return new BorrowCommand(store, customer, movie);
    }
  }

  // data does not match customer or movie
  std::cout << "Invalid movie " << " for customer " << customer->getLastName()
            << " " << customer->getFirstName()
            << ", discarding line: " << std::endl;
  return nullptr;
}

// Executes the borrow command and updates inventory and transaction history
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

  // Movie could not be borrowed because it is unavailable
  std::cout << "Failed to execute command: Borrow " << customer->getLastName()
            << " " << customer->getFirstName() << " " << movie->getTitle()
            << std::endl;
}