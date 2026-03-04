#include "Drama.h"

Movie *DramaMovieFactory::makeMovie(std::string data) const {
  // format: "D, stock, director, title, year"

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

  return new Drama(stock, director, title, year);
}

void Drama::print() const {
  std::cout << "Drama: " << getStock() << ", " << getDirector() << ", "
            << getTitle() << ", " << getYear() << std::endl;
}

bool Drama::isEqual(const Movie &other) const {
  if (getGenre() != other.getGenre()) {
    return false;
  }

  const Drama &otherDrama = static_cast<const Drama &>(other);
  return getDirector() == otherDrama.getDirector() &&
         getTitle() == otherDrama.getTitle();
}

bool Drama::isEqual(const std::string &data) const {
  // expected format: " director, title,"
  size_t pos = data.find(',');
  if (pos == std::string::npos) {
    return false;
  }

  std::string director = data.substr(1, pos - 1);

  size_t start = pos + 2;
  pos = data.find(',', start);
  std::string title = data.substr(start, pos - start);

  return getDirector() == director && getTitle() == title;
}