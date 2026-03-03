#include "Movie.h"

// Getter functions

std::string Movie::getTitle() const {
    return title;
}

std::string Movie::getDirector() const {
    return director;
}

char Movie::getGenre() const {
    return genre;
}

int Movie::getStock() const {
    return stock;
}

int Movie::getYear() const {
    return year;
}

// Stock management functions

bool Movie::increaseStock() {
  stock++;
  return true;
}

bool Movie::decreaseStock() {
  if (stock <= 0) {
    return false;
  }
  stock--;
  return true;
}

bool Movie::isAvailable() const {
  //
  return stock > 0;
}