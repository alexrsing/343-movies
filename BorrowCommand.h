#ifndef BORROWCOMMAND_H
#define BORROWCOMMAND_H

#include "Command.h"
#include "Customer.h"
#include "Movie.h"
#include <string>

/*
Defines the command used to borrow a movie from the store.

The BorrowCommand is responsible for:
- identifying the correct customer
- identifying the correct movie
- updating inventory
- recording the transaction in the customer's history
*/

// Factory class responsible for creating BorrowCommand objects
class BorrowCommandFactory : public CommandFactory {
public:
  // Parses command input and creates a BorrowCommand
  BorrowCommandFactory();
  Command *createCommand(std::string data, MovieStore *store) const override;
};
/*
Represents the command that allows a customer to borrow a movie.
When executed, it updates the store inventory and records
the borrow transaction for the customer.
*/
class BorrowCommand : public Command {
public:
  // Constructor initializes store, customer, and movie references
  BorrowCommand(MovieStore *store, Customer *customer, Movie *movie)
      : Command(store), customer(customer), movie(movie) {}

  // Executes the borrow command, updating inventory and recording the
  // transaction
  void execute() override;

private:
  // Customer performing the borrow operation
  Customer *customer;

  // Movie being borrowed
  Movie *movie;
};

#endif
