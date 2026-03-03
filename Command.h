#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command;

class CommandFactory {
public:
  virtual Command *createCommand(std::string data) const = 0;
};

class Command {
public:
  virtual ~Command() = default;
};

#endif