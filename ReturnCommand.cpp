#include "ReturnCommand.h"
#include <sstream>

// Factory constructor
ReturnCommandFactory::ReturnCommandFactory() {}

Command *ReturnCommandFactory::createCommand(std::string data,
                                             MovieStore *store) const {
  // parse data from input string into ReturnCommand constructor parameters
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
      return new ReturnCommand(store, customer, movie);
    }
  }

  // data does not match customer or movie
  std::cout << "Invalid return command data: " << data << std::endl;
  return nullptr;
}

void ReturnCommand::execute() {
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

  if (store->returnMovie(customer, movie)) {
    customer->addTransaction('R', movie);
    return;
  }
}