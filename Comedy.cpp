#include "Comedy.h"

Movie *ComedyMovieFactory::makeMovie(std::string data) const {
  // format: "F, stock, director, title, year"
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

void Comedy::print() const {
  std::cout << "Comedy: " << getStock() << " in, " << getBorrowed() << " out, "
            << getDirector() << ", " << getTitle() << ", " << getYear()
            << std::endl;
}

bool Comedy::isEqual(const Movie &other) const {
  if (getGenre() != other.getGenre()) {
    return false;
  }

  const Comedy &otherComedy = static_cast<const Comedy &>(other);
  return getTitle() == otherComedy.getTitle() &&
         getDirector() == otherComedy.getDirector();
}

bool Comedy::isEqual(const std::string &data) const {
  // expected format: " title, year"
  size_t pos = data.find(',');
  if (pos == std::string::npos) {
    return false;
  }

  std::string title = data.substr(1, pos - 1);
  int year = std::stoi(data.substr(pos + 2));

  return getTitle() == title && getYear() == year;
}

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