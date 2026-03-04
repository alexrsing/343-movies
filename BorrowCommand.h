#ifndef BORROWCOMMAND_H
#define BORROWCOMMAND_H

#include "Command.h"
#include <string>

class BorrowCommandFactory : public CommandFactory {
public:
  BorrowCommandFactory();
  Command *createCommand(std::string data) const override;
};

class BorrowCommand : public Command {
public:
  BorrowCommand(int customerID, std::string mediaType, std::string movieType);

private:
  int customerID;
  std::string mediaType;
  std::string movieType;
};

#endif
