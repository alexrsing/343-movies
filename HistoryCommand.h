#ifndef HISTORYCOMMAND_H
#define HISTORYCOMMAND_H

#include "Command.h"

class HistoryCommandFactory : public CommandFactory {
public:
  HistoryCommandFactory();
  Command *createCommand(std::string data) const override;
};

class HistoryCommand : public Command {
public:
  HistoryCommand();
};

#endif