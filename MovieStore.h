#ifndef MOVIESTORE_H
#define MOVIESTORE_H

#include "Command.h"
#include "Customer.h"
#include "Movie.h"
#include "MyHashTable.h"
#include <string>
#include <utility>
#include <vector>

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

private:
  MyHashTable<char, MovieFactory *> movieFactories;
  MyHashTable<char, CommandFactory *> commandFactories;
  MyHashTable<char, std::vector<Movie *>> inventory;
  MyHashTable<int, Customer *> customers;
  std::vector<Command *> commands;
  std::vector<char> genres;
  std::vector<char> mediaTypes;
};

#endif