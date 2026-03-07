#include "Movie.h"

// Getter functions

/**
 * Returns the movie title.
 */
std::string Movie::getTitle() const { return title; }

/**
 * Returns the movie director.
 */
std::string Movie::getDirector() const { return director; }

/**
 * Returns the movie genre code.
 */
char Movie::getGenre() const { return genre; }

/**
 * Returns the current stock of the movie.
 */
int Movie::getStock() const { return stock; }

/**
 * Returns how many copies of the movie have been borrowed.
 */
int Movie::getBorrowed() const { return initialStock - stock; }

/**
 * Returns the release year of the movie.
 */
int Movie::getYear() const { return year; }

// Stock management functions

/**
 * Increases the stock when a movie is returned.
 */
bool Movie::increaseStock() {
  stock++;
  return true;
}

/**
 * Decreases the stock when a movie is borrowed.
 */
bool Movie::decreaseStock() {
  if (stock <= 0) {
    return false;
  }
  stock--;
  return true;
}

/**
 * Checks if the movie is available for borrowing.
 */
bool Movie::isAvailable() const { return stock > 0; }