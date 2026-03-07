#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>

/**
 * Base class representing a movie in the store inventory.
 *
 * A Movie stores basic information such as title, director,
 * genre, release year, and stock count.
 *
 * Abstract class extended by specific movie
 * types such as Comedy, Drama, and Classic.
 *
 * Provides functions for managing stock and
 * comparing movies.
 */

class Movie;

/**
 * Factory class used to create Movie objects.
 */
class MovieFactory {
public:
  virtual ~MovieFactory() = default;

  /**
   * Creates a Movie object from a line of input data.
   */
  virtual Movie *makeMovie(std::string data) const = 0;
};

class Movie {
private:
  std::string title;
  std::string director;
  char genre;
  int stock;
  int initialStock;
  int year;

public:
  /**
   * Constructs a Movie object.
   *
   * Stores basic movie information and initializes
   * stock values.
   */
  Movie(std::string title, std::string director, char genre, int stock,
        int year)
      : title(title), director(director), genre(genre), stock(stock),
        initialStock(stock), year(year) {};

  // Virtual destructor for proper cleanup of derived movie objects
  virtual ~Movie() = default;

  // Getter functions

  /**
   * Returns the movie title.
   */
  std::string getTitle() const;

  /**
   * Returns the movie director.
   */
  std::string getDirector() const;

  /**
   * Returns the movie genre.
   */
  char getGenre() const;

  /**
   * Returns the current stock of the movie.
   */
  int getStock() const;

  /**
   * Returns how many copies of the movie have been borrowed.
   */
  int getBorrowed() const;

  /**
   * Returns the release year of the movie.
   */
  int getYear() const;

  // Stock management functions

  /**
   * Increases the stock when a movie is returned.
   */
  bool increaseStock();

  /**
   * Decreases the stock when a movie is borrowed.
   */
  bool decreaseStock();

  /**
   * Checks if the movie is available for borrowing.
   */
  bool isAvailable() const;

  /**
   * Prints the movie information.
   */
  virtual void print() const = 0;

  /**
   * Compares two movie objects to check if they are the same movie.
   */
  virtual bool isEqual(const Movie &other) const = 0;

  /**
   * Compares a movie object with input data to check if they match.
   */
  virtual bool isEqual(const std::string &data) const = 0;

  /**
   * Comparison operator used for sorting movies.
   */
  virtual bool operator>(const Movie &other) const = 0;
};

#endif