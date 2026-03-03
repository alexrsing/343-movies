#include "BorrowCommand.h"
#include <sstream>

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

BorrowCommand::BorrowCommand(int customerID, const std::string mediaType,
                             const std::string movieType) {
  // initialize BorrowCommand object with constructor parameters
  (void)customerID;
  (void)mediaType;
  (void)movieType;
}