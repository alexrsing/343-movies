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

  return new Classic(stock, director, title,
                     actorFirst, actorLast,
                     month, year);
}

void Classic::print() const {
  std::cout << "Classic: " << getStock() << ", "
            << getDirector() << ", "
            << getTitle() << ", "
            << actorFirst << " "
            << actorLast << " "
            << month << " "
            << getYear() << std::endl;
}

bool Classic::isEqual(const Movie &other) const {
  if (getGenre() != other.getGenre()) {
    return false;
  }

  const Classic &otherClassic = static_cast<const Classic &>(other);

  return getYear() == otherClassic.getYear() &&
         month == otherClassic.month &&
         actorFirst == otherClassic.actorFirst &&
         actorLast == otherClassic.actorLast;
}

int Classic::getMonth() const {
  return month;
}