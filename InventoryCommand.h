#ifndef INVENTORYCOMMAND_H
#define INVENTORYCOMMAND_H

#include "Command.h"

// Factory class for creating InventoryCommand objects
class InventoryCommandFactory : public CommandFactory {
public:
  // Default constructor for InventoryCommandFactory
  InventoryCommandFactory();

  // Creates an InventoryCommand from input command data
  Command *createCommand(std::string data, MovieStore *store) const override;
};

// Command class for handling inventory display in the MovieStore
class InventoryCommand : public Command {
public:
  // Constructor for InventoryCommand that takes a pointer to the MovieStore
  explicit InventoryCommand(MovieStore *store) : Command(store) {};

  // Executes the inventory command and prints the store's inventory
  void execute() override;
};

#endif