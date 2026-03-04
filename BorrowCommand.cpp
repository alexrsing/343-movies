#include "BorrowCommand.h"
#include <sstream>

// Factory constructor
BorrowCommandFactory::BorrowCommandFactory() {}

Command *BorrowCommandFactory::createCommand(std::string data) const {
  // parse data from input string into BorrowCommand constructor parameters
  std::istringstream iss(data);
  int customerID;
  std::string mediaType;
  std::string movieType;

  iss >> customerID >> mediaType >> movieType;

  // Return a new BorrowCommand object
  return new BorrowCommand(customerID, mediaType, movieType);
}

BorrowCommand::BorrowCommand(int customerID, std::string mediaType,
                             std::string movieType)
    : customerID(customerID), mediaType(mediaType), movieType(movieType) {}