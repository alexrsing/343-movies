#include "InventoryCommand.h"
#include "MovieStore.h"
#include <sstream>

static bool registered = [] {
  MovieStore::registerCommandFactory('I', new InventoryCommandFactory());
  return true;
}();

InventoryCommandFactory::InventoryCommandFactory() {}

Command *InventoryCommandFactory::createCommand(std::string /*data*/,
                                                MovieStore *store) const {
  return new InventoryCommand(store);
}

void InventoryCommand::execute() {
  // print stores inventory object
  getStore()->printInventory();
}