#ifndef HISTORYCOMMAND_H
#define HISTORYCOMMAND_H

#include "Command.h"
#include "Customer.h"

// Factory for creating HistoryCommand objects
class HistoryCommandFactory : public CommandFactory {
public:
  // Default constructor for HistoryCommandFactory
  HistoryCommandFactory();

  // Creates a HistoryCommand from input command data
  Command *createCommand(std::string data, MovieStore *store) const override;
};

// Command for printing a customer's transaction history
class HistoryCommand : public Command {
public:
  // Constructor for HistoryCommand
  HistoryCommand(MovieStore *store, Customer *customer)
      : Command(store), customer(customer) {}

  // Executes the history command and prints customer transactions
  void execute() override;

private:
  // Pointer to the customer whose history we want to print
  Customer *customer;
};

#endif