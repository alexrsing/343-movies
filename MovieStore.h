#ifndef MOVIESTORE_H
#define MOVIESTORE_H

#include "Command.h"
#include "Customer.h"
#include "Movie.h"
#include "MyHashTable.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

/*
Represents an entry in the movie factory registry.
Stores the factory pointer and sorting priority.
*/
struct MovieFactoryEntry {
  int priority;
  MovieFactory *factory;
};

/*
Main class to manage the movie rental store.

MovieStore is responsible for:
- Storing movies in inventory
- Managing customers
- Processing commands (borrow, return, history, inventory)
- Loading data from input files
*/
class MovieStore {
public:
  MovieStore();
  ~MovieStore();

  // Borrow and return operations
  bool returnMovie(Customer *customer, Movie *movie);
  bool borrowMovie(Customer *customer, Movie *movie);

  // Display store inventory
  void printInventory();

  // Load data from files
  void populateInventory(std::string filePath);
  void populateCustomers(std::string filePath);
  void populateCommands(std::string filePath);

  // Execute all commands in the order they were read from the file
  void executeCommands();

  // Retrieve customer by ID
  Customer *getCustomer(int id);

  // Retrieve movies of a given genre
  std::vector<Movie *> &getMovies(char genre);

  // Check if media type is valid
  bool validMediaType(char type) const;

  // Register factories for movie and command creation
  static void registerMovieFactory(char code, int priority,
                                   MovieFactory *factory);
  static void registerCommandFactory(char code, CommandFactory *factory);

private:
  // Factories used to create movie objects
  MyHashTable<char, MovieFactory *> movieFactories;

  // Factories used to create command objects
  MyHashTable<char, CommandFactory *> commandFactories;

  // Inventory of movies grouped by genre
  MyHashTable<char, std::vector<Movie *>> inventory;

  // Customers stored by ID
  MyHashTable<int, Customer *> customers;

  // Customers stored by ID
  std::vector<Command *> commands;

  // Order of genres for printing inventory
  std::vector<char> genres;

  // Supported media types
  std::vector<char> mediaTypes;

  // Static registries for factories
  static std::map<char, MovieFactoryEntry> &getMovieRegistry();
  static std::map<char, CommandFactory *> &getCommandRegistry();
};

#endif
