#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>

class Movie;

class MovieFactory {
public:
  virtual ~MovieFactory() = default;
  virtual Movie *makeMovie(std::string data) const = 0;
};

class Movie {
private:
  std::string title;
  std::string director;
  char genre;
  int stock;
  int year;

public:
  virtual ~Movie() = default;
  Movie(std::string title, std::string director, char genre, int stock,
        int year)
      : title(title), director(director), genre(genre), stock(stock),
        year(year) {};

  std::string getTitle() const;
  std::string getDirector() const;
  char getGenre() const;
  int getStock() const;
  int getYear() const;

  bool increaseStock();
  bool decreaseStock();
  bool isAvailable() const;

  virtual void print() const = 0;
  virtual bool isEqual(const Movie &other) const = 0;
  virtual bool isEqual(const std::string &data) const = 0;
};
#endif