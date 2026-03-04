#ifndef BORROWCOMMAND_H
#define BORROWCOMMAND_H

#include "Command.h"
#include <string>

class BorrowCommandFactory : public CommandFactory {
public:
  BorrowCommandFactory();
  Command *createCommand(std::string data, MovieStore *store) const override;
};

class BorrowCommand : public Command {
public:
  BorrowCommand(MovieStore *store, Customer *customer, Movie *movie)
      : Command(store), customer(customer), movie(movie) {}
  void execute() override;

private:
  Customer *customer;
  Movie *movie;
};

#endif
