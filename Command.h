#ifndef COMMAND_H
#define COMMAND_H

#include <string>

// Forward declaration of MovieStore to avoid circular dependency
class MovieStore;

/*
Abstract base class for all store commands.
Each command performs an action when execute() is called.
*/
class Command;

// Factory class used to create command objects from input data
class CommandFactory {
public:
  virtual ~CommandFactory() = default;
  virtual Command *createCommand(std::string data, MovieStore *store) const = 0;
};

/*
Base classes for all commands in the movie store system.

Commands represent operations such as:
- Borrow movie
- Return movie
- Print inventory
- Show customer history

Each command is created using a factory and executed
through the execute() function.
*/
class Command {
public:
  // Constructor storing a reference to the MovieStore
  explicit Command(MovieStore *store) : store(store) {}

  // Virtual destructor for proper cleanup of derived command objects
  virtual ~Command() = default;

  // Executes the command action
  virtual void execute() = 0;

  // Returns the associated MovieStore
  MovieStore *getStore() const { return store; }

private:
// Reference to the MovieStore that the command will operate on
  MovieStore *store;
};

#endif