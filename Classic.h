#ifndef CLASSIC_H
#define CLASSIC_H

#include "Movie.h"

/*
Factory class used to create Classic movie objects
from inventory file input data.
*/
class ClassicMovieFactory : public MovieFactory {
public:
  // Creates a Classic movie object from a line of input data
  Movie *makeMovie(std::string data) const override;
};

/*
Represents a Classic genre movie.

Classic movies are uniquely identified by:
- release year
- release month
- major actor (first and last name)

They are sorted by year, then month, then actor name.
*/
class Classic : public Movie {
private:
  // Factory used to create Classic objects
  static ClassicMovieFactory factory;

  // Major actor's first name
  std::string actorFirst;

  // Major actor's last name
  std::string actorLast;

  // Month the movie was released
  int month;

public:
  // Constructor initializes classic movie attributes
  Classic(int stock, std::string director, std::string title,
          std::string actorFirst, std::string actorLast, int month, int year)
      : Movie(title, director, 'C', stock, year), actorFirst(actorFirst),
        actorLast(actorLast), month(month) {}

  // Returns the release month
  int getMonth() const;

  // Returns actor first name
  std::string getActorFirst() const;

  // Returns actor last name
  std::string getActorLast() const;

  // Print the classic movie's information
  void print() const override;

  // Compares this movie with another movie object
  bool isEqual(const Movie &other) const override;

  // Compares movie with parsed input data
  bool isEqual(const std::string &data) const override;

  // Comparison operator used for sorting classic movies
  bool operator>(const Movie &other) const override;
};

#endif