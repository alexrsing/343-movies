#include "Classic.h"
#include <sstream>

Movie *ClassicMovieFactory::makeMovie(std::string data) const {
  // format:
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

void Classic::print() const {
  std::cout << "Classic: " << getStock() << ", " << getDirector() << ", "
            << getTitle() << ", " << actorFirst << " " << actorLast << " "
            << month << " " << getYear() << std::endl;
}

bool Classic::isEqual(const Movie &other) const {
  if (getGenre() != other.getGenre()) {
    return false;
  }

  const Classic &otherClassic = static_cast<const Classic &>(other);

  return getYear() == otherClassic.getYear() && month == otherClassic.month &&
         actorFirst == otherClassic.actorFirst &&
         actorLast == otherClassic.actorLast;
}

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

int Classic::getMonth() const { return month; }

bool Classic::operator>(const Movie &other) const {
  if (getGenre() != other.getGenre()) {
    throw std::invalid_argument("Cannot compare movies of different genres");
  }

  const Classic &otherClassic = static_cast<const Classic &>(other);
  // Sort by title first
  if (getTitle() != otherClassic.getTitle()) {
    return getTitle() > otherClassic.getTitle();
  }
  if (getYear() != otherClassic.getYear()) {
    return getYear() > otherClassic.getYear();
  }
  if (month != otherClassic.month) {
    return month > otherClassic.month;
  }
  if (actorLast != otherClassic.actorLast) {
    return actorLast > otherClassic.actorLast;
  }
  return actorFirst > otherClassic.actorFirst;
}