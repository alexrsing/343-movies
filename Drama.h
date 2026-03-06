#ifndef DRAMA_H
#define DRAMA_H

#include "Movie.h"

class DramaMovieFactory : public MovieFactory {
public:
  Movie *makeMovie(std::string data) const override;
};

class Drama : public Movie {
private:
  static DramaMovieFactory factory;

public:
  Drama(int stock, std::string director, std::string title, int year)
      : Movie(title, director, 'D', stock, year) {}

  void print() const override;
  bool isEqual(const Movie &other) const override;
  bool isEqual(const std::string &data) const override;

  bool operator>(const Movie &other) const override;
};

#endif