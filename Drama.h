#ifndef DRAMA_H
#define DRAMA_H

#include "Movie.h"

/*
Factory class responsible for creating Drama movie objects
from inventory file input data.
*/
class DramaMovieFactory : public MovieFactory {
public:
  Movie *makeMovie(std::string data) const override;
};

/*
Represents a Drama genre movie.

Drama movies are identified by:
- director
- title

They are sorted by director name and then title.
*/
class Drama : public Movie {
private:
  // Factory used to create Drama movie objects
  static DramaMovieFactory factory;

public:
  // Constructor initializes drama movie attributes
  Drama(int stock, std::string director, std::string title, int year)
      : Movie(title, director, 'D', stock, year) {}

  // Prints drama movie information
  void print() const override;

  // Compares this movie with another movie object
  bool isEqual(const Movie &other) const override;

  // Comparison operator used for sorting drama movies
  bool isEqual(const std::string &data) const override;

  // Comparison operator used for sorting drama movies
  bool operator>(const Movie &other) const override;
};

#endif