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
  BorrowCommand(int customerID, const std::string mediaType,
                const std::string movieType);
};

#endif
