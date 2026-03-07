#ifndef COMEDYMOVIE_H
#define COMEDYMOVIE_H

#include "Movie.h"

/*
Factory class used to create Comedy movie objects
from inventory input data.
*/
class ComedyMovieFactory : public MovieFactory {
public:
  // Creates a Comedy movie object from a formatted string of data
  Movie *makeMovie(std::string data) const override;
};

/*
Represents a Comedy genre movie.

Comedy movies are identified by:
- title
- release year

They are sorted alphabetically by title, then by year.
*/
class Comedy : public Movie {
private:
  // Factory used to register and create Comedy movies
  static ComedyMovieFactory factory;

public:
  // Constructor initializes comedy movie attributes
  Comedy(int stock, std::string director, std::string title, int year)
      : Movie(title, director, 'F', stock, year) {};

  // Prints comedy movie information
  void print() const override;

  // Compares this movie with another movie object
  bool isEqual(const Movie &other) const override;

  // Compares movie with parsed search data
  bool isEqual(const std::string &data) const override;

  // Comparison operator used for sorting comedy movies
  bool operator>(const Movie &other) const override;
};

#endif