#include "InventoryCommand.h"
#include "MovieStore.h"
#include <sstream>

// Registers the Inventory command with the MovieStore
static bool registered = [] {
  MovieStore::registerCommandFactory('I', new InventoryCommandFactory());
  return true;
}();

// Default constructor for InventoryCommandFactory
InventoryCommandFactory::InventoryCommandFactory() {}

// Creates an InventoryCommand from input command data
Command *InventoryCommandFactory::createCommand(std::string /*data*/,
                                                MovieStore *store) const {
  return new InventoryCommand(store);
}

// Executes the inventory command and prints the store's inventory
void InventoryCommand::execute() {
  // print stores inventory object
  getStore()->printInventory();
}