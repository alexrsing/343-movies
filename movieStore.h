#ifndef MOVIESTORE_H
#define MOVIESTORE_H

#include "movie.h"
#include "myHashTable.h"
#include <string>
#include <utility>
#include <vector>

class MovieStore {
  public:
    bool returnMovie(Movie movie);
    bool borrowMovie(Movie movie);
    void printInventory();

    void populateInventory(std::string filePath);

  private:
    MyHashTable<std::string, Movie *> inventory;
};

#endif