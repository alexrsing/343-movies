#ifndef INVENTORYCOMMAND_H
#define INVENTORYCOMMAND_H

#include "Command.h"

class InventoryCommandFactory : public CommandFactory {
public:
  InventoryCommandFactory();
  Command *createCommand(std::string data) const override;
};

class InventoryCommand : public Command {
public:
  InventoryCommand();
};

#endif