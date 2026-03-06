#include "ReturnCommand.h"
#include "MovieStore.h"
#include <iostream>
#include <sstream>

// Factory constructor
ReturnCommandFactory::ReturnCommandFactory() {}

Command *ReturnCommandFactory::createCommand(std::string data,
                                             MovieStore *store) const {
  // parse data from input string into ReturnCommand constructor parameters
  // skip command type character at start of line
  if (data.length() < 2) {
    std::cout << "Invalid return command data: " << data << std::endl;
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

  // Check if movie is currently borrowed by this customer
  if (!customer->hasBorrowed(movie)) {
    std::cout << "Customer has not borrowed this movie" << std::endl;
    return;
  }

  if (store->returnMovie(customer, movie)) {
    customer->addTransaction('R', movie);
    return;
  }
}