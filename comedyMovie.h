#ifndef COMEDYMOVIE_H
#define COMEDYMOVIE_H

#include "movie.h"

class ComedyMovieFactory : public MovieFactory {
public:
  Movie *makeMovie() const override;
};

class ComedyMovie : public Movie {
private:
  static ComedyMovieFactory factory;
public:
  ComedyMovie();
};

#endif