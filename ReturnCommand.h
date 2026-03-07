#ifndef RETURNCOMMAND_H
#define RETURNCOMMAND_H

#include "Command.h"
#include "Customer.h"
#include "Movie.h"

/*
Defines the command used to return a movie to the store.

The ReturnCommand is responsible for:
- identifying the correct customer
- identifying the correct movie
- increasing the movie stock
- recording the return transaction in the customer's history
*/

// Factory class responsible for creating ReturnCommand objects
class ReturnCommandFactory : public CommandFactory {
public:
  // Default constructor for ReturnCommandFactory
  ReturnCommandFactory();

  // Parses input data and creates a ReturnCommand
  Command *createCommand(std::string data, MovieStore *store) const override;
};

/*
Represents the command that allows a customer to return a movie.

When executed, the command:
- verifies the customer and movie
- checks that the movie was borrowed
- updates the inventory
- records the return transaction
*/
class ReturnCommand : public Command {
public:
  // Constructor initializes store, customer, and movie references
  ReturnCommand(MovieStore *store, Customer *customer, Movie *movie)
      : Command(store), customer(customer), movie(movie) {}

  // Executes the return operation
  void execute() override;

private:
  // Customer performing the return
  Customer *customer;

  // Movie being returned
  Movie *movie;
};

#endif