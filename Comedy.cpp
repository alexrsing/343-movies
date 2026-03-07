#include "Comedy.h"
#include "MovieStore.h"

static bool registered = [] {
  // Registers the Comedy movie factory with the MovieStore
  MovieStore::registerMovieFactory('F', 0, new ComedyMovieFactory());
  return true;
}();

// Creates a Comedy movie object from a line of inventory input data
Movie *ComedyMovieFactory::makeMovie(std::string data) const {
  // Format: "F, stock, director, title, year"
  size_t pos = data.find(',');

  size_t start = pos + 2;
  pos = data.find(',', start);
  int stock = std::stoi(data.substr(start, pos - start));

  start = pos + 2;
  pos = data.find(',', start);
  std::string director = data.substr(start, pos - start);

  start = pos + 2;
  pos = data.find(',', start);
  std::string title = data.substr(start, pos - start);

  start = pos + 2;
  int year = std::stoi(data.substr(start));

  return new Comedy(stock, director, title, year);
}

// Displays comedy movie information including stock and year
void Comedy::print() const {
  // Title, year, director, stock, genere
  std::cout << getTitle() << ", " << getYear() << ", " << getDirector() << " ("
            << getStock() << ") - Comedy" << std::endl;
}

// Checks if two comedy movies represent the same movie
bool Comedy::isEqual(const Movie &other) const {
  if (getGenre() != other.getGenre()) {
    return false;
  }

  const Comedy &otherComedy = static_cast<const Comedy &>(other);
  return getTitle() == otherComedy.getTitle() &&
         getDirector() == otherComedy.getDirector();
}

// Checks if the movie matches search data from command input
bool Comedy::isEqual(const std::string &data) const {
  // Expected format: " title, year"
  size_t pos = data.find(',');
  if (pos == std::string::npos) {
    return false;
  }

  std::string title = data.substr(1, pos - 1);
  int year = std::stoi(data.substr(pos + 2));

  return getTitle() == title && getYear() == year;
}

// Defines sorting order for comedy movies
// Sorted by title first, then by release year
bool Comedy::operator>(const Movie &other) const {
  if (getGenre() != other.getGenre()) {
    throw std::invalid_argument("Cannot compare movies of different genres");
  }

  const Comedy &otherComedy = static_cast<const Comedy &>(other);
  if (getTitle() != otherComedy.getTitle()) {
    return getTitle() > otherComedy.getTitle();
  }
  return getYear() > otherComedy.getYear();
}