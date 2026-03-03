#include "Movie.h"

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