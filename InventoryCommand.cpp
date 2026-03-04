#include "InventoryCommand.h"
#include <sstream>

// Factory constructor
InventoryCommandFactory::InventoryCommandFactory() {}

Command *InventoryCommandFactory::createCommand(std::string data,
                                                MovieStore *store) const {
  return new InventoryCommand(store);
}

void InventoryCommand::execute() {
  // print stores inventory object
  getStore()->printInventory();
}