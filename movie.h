#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>

class MovieFactory {
public:
  virtual Movie *makeMovie() const = 0;
};

class Movie {
private:
  std::string name;
  std::string genre;
  std::string director;
  int stock;
  int year;

  bool increaseStock();
  bool decreaseStock();
  bool isAvailable() const;

public:
  std::string getName() const;
  std::string getGenre() const;
  std::string getDirector() const;
  int getStock() const;
  int getYear() const;
};
#endif