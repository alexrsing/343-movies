#ifndef RETURNCOMMAND_H
#define RETURNCOMMAND_H

#include "Command.h"

class ReturnCommandFactory : public CommandFactory {
public:
  ReturnCommandFactory();
  Command *createCommand(std::string data, MovieStore *store) const override;
};

class ReturnCommand : public Command {
public:
  ReturnCommand(MovieStore *store, Customer *customer, Movie *movie)
      : Command(store), customer(customer), movie(movie) {}
  void execute() override;

private:
  Customer *customer;
  Movie *movie;
};

#endif