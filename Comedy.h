#ifndef COMEDYMOVIE_H
#define COMEDYMOVIE_H

#include "Movie.h"

class ComedyMovieFactory : public MovieFactory {
public:
  Movie *makeMovie(std::string data) const override;
};

class Comedy : public Movie {
private:
  static ComedyMovieFactory factory;

public:
  Comedy(int stock, std::string director, std::string title, int year)
      : Movie(title, director, 'F', stock, year) {};
  void print() const override;
  bool isEqual(const Movie &other) const override;
  bool isEqual(const std::string &data) const override;
};

#endif