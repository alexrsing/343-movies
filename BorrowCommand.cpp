#include "BorrowCommand.h"

Command *BorrowCommandFactory::createCommand(std::string data) const {
  // parse data from input string into BorrowCommand constructor parameters
}

BorrowCommand::BorrowCommand(int customerID, const std::string mediaType,
                             const std::string movieType) {
  // initialize BorrowCommand object with constructor parameters
}