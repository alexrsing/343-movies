#ifndef CLASSIC_H
#define CLASSIC_H

#include "Movie.h"

class ClassicMovieFactory : public MovieFactory {
public:
  Movie *makeMovie(std::string data) const override;
};

class Classic : public Movie {
private:
  static ClassicMovieFactory factory;

  std::string actorFirst;
  std::string actorLast;
  int month;

public:
  Classic(int stock, std::string director, std::string title,
          std::string actorFirst, std::string actorLast, int month, int year)
      : Movie(title, director, 'C', stock, year), actorFirst(actorFirst),
        actorLast(actorLast), month(month) {}

  void print() const override;
  bool isEqual(const Movie &other) const override;
  bool isEqual(const std::string data) const override;

  int getMonth() const;
};

#endif