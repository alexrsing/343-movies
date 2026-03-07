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

struct MovieFactoryEntry {
  int priority;
  MovieFactory *factory;
};

class MovieStore {
public:
  MovieStore();
  ~MovieStore();
  bool returnMovie(Customer *customer, Movie *movie);
  bool borrowMovie(Customer *customer, Movie *movie);
  void printInventory();

  void populateInventory(std::string filePath);
  void populateCustomers(std::string filePath);
  void populateCommands(std::string filePath);
  void executeCommands();

  Customer *getCustomer(int id);
  std::vector<Movie *> &getMovies(char genre);
  bool validMediaType(char type) const;

  static void registerMovieFactory(char code, int priority,
                                   MovieFactory *factory);
  static void registerCommandFactory(char code, CommandFactory *factory);

private:
  MyHashTable<char, MovieFactory *> movieFactories;
  MyHashTable<char, CommandFactory *> commandFactories;
  MyHashTable<char, std::vector<Movie *>> inventory;
  MyHashTable<int, Customer *> customers;
  std::vector<Command *> commands;
  std::vector<char> genres;
  std::vector<char> mediaTypes;

  static std::map<char, MovieFactoryEntry> &getMovieRegistry();
  static std::map<char, CommandFactory *> &getCommandRegistry();
};

#endif
