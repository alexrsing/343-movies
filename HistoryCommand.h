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
  HistoryCommand(MovieStore *store, Customer *customer, Movie *movie)
      : Command(store), customer(customer), movie(movie) {}
  void execute() override;

private:
  Customer *customer;
  Movie *movie;
};

#endif