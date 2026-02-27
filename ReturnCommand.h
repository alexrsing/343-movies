#ifndef RETURNCOMMAND_H
#define RETURNCOMMAND_H

#include "Command.h"

class ReturnCommandFactory : public CommandFactory {
public:
  ReturnCommandFactory();
  Command *createCommand(std::string data) const override;
};

class ReturnCommand : public Command {
public:
  ReturnCommand();
};

#endif