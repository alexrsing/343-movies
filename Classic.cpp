#include "Classic.h"
#include "MovieStore.h"
#include <sstream>

// Registers the Classic movie factory with the MovieStore
static bool registered = [] {
  MovieStore::registerMovieFactory('C', 2, new ClassicMovieFactory());
  return true;
}();

// Creates a Classic movie object from a line of inventory input data
Movie *ClassicMovieFactory::makeMovie(std::string data) const {
  // Format:
  // C, stock, director, title, actorFirst actorLast month year

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
  std::string remaining = data.substr(start);

  std::stringstream ss(remaining);

  std::string actorFirst;
  std::string actorLast;
  int month;
  int year;

  ss >> actorFirst >> actorLast >> month >> year;

  return new Classic(stock, director, title, actorFirst, actorLast, month,
                     year);
}

// Displays classic movie information including stock and actor
void Classic::print() const {
  std::cout << "Classic: " << getStock() << " in, " << getBorrowed() << " out, "
            << getDirector() << ", " << getTitle() << ", " << actorFirst << " "
            << actorLast << " " << month << " " << getYear() << std::endl;
}

// Checks if two classic movies represent the same movie
bool Classic::isEqual(const Movie &other) const {
  if (getGenre() != other.getGenre()) {
    return false;
  }

  const Classic &otherClassic = static_cast<const Classic &>(other);

  return getYear() == otherClassic.getYear() && month == otherClassic.month &&
         actorFirst == otherClassic.actorFirst &&
         actorLast == otherClassic.actorLast;
}

// Checks if movie matches search data from command input
bool Classic::isEqual(const std::string &data) const {
  // expected format: " month year actorFirst actorLast"
  std::istringstream iss(data);
  int m;
  int y;
  std::string aFirst;
  std::string aLast;

  iss >> m >> y >> aFirst >> aLast;

  return month == m && getYear() == y && actorFirst == aFirst &&
         actorLast == aLast;
}

// Returns the release month of the classic movie
int Classic::getMonth() const { return month; }

// Defines sorting order for classic movies
// Sorted by year, then month, then major actor name
bool Classic::operator>(const Movie &other) const {
  if (getGenre() != other.getGenre()) {
    throw std::invalid_argument("Cannot compare movies of different genres");
  }

  const Classic &otherClassic = static_cast<const Classic &>(other);
  // Sort by release date first, then major actor
  if (getYear() != otherClassic.getYear()) {
    return getYear() > otherClassic.getYear();
  }
  if (month != otherClassic.month) {
    return month > otherClassic.month;
  }
  if (actorFirst != otherClassic.actorFirst) {
    return actorFirst > otherClassic.actorFirst;
  }
  return actorLast > otherClassic.actorLast;
}