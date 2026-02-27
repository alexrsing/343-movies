#ifndef COMEDYMOVIE_H
#define COMEDYMOVIE_H

#include "Movie.h"

class ComedyMovieFactory : public MovieFactory {
public:
  Movie *makeMovie(std::string data) const override;
};

class ComedyMovie : public Movie {
private:
  static ComedyMovieFactory factory;

public:
  ComedyMovie(int stock, std::string director, std::string title, int year);
  void print() const override;
  bool isEqual(const Movie &other) const override;
};

#endif