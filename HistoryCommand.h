#ifndef HISTORYCOMMAND_H
#define HISTORYCOMMAND_H

#include "Command.h"

class HistoryCommandFactory : public CommandFactory {
public:
  HistoryCommandFactory();
  Command *createCommand(std::string data, MovieStore *store) const override;
};

class HistoryCommand : public Command {
public:
  HistoryCommand(MovieStore *store, Customer *customer)
      : Command(store), customer(customer) {}
  void execute() override;

private:
  Customer *customer;
};

#endif