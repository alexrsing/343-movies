#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class MovieStore;
class Command;

class CommandFactory {
public:
  virtual ~CommandFactory() = default;
  virtual Command *createCommand(std::string data, MovieStore *store) const = 0;
};

class Command {
public:
  explicit Command(MovieStore *store) : store(store) {}
  virtual ~Command() = default;
  virtual void execute() = 0;
  MovieStore *getStore() const { return store; }

private:
  MovieStore *store;
};

#endif