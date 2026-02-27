#include "MovieStore.h"
#include <fstream>

bool MovieStore::returnMovie(Customer *customer, Movie *movie) {
  // Check if the customer exists in the customers hash table
  if (!customers.contains(std::to_string(customer->getID()))) {
    // throw runtime error if customer does not exist
    throw std::runtime_error("Customer not found");
  }

  // Check if the movie exists in the inventory hash table
  if (!inventory.contains(movie->getGenre())) {
    // throw runtime error if genre does not exist
    throw std::runtime_error("Genre not found");
  }

  // Increment the stock of the movie in the inventory
  std::vector<Movie *> &movies = inventory.get(movie->getGenre());
  for (Movie *m : movies) {
    if (m == movie) {
      m->increaseStock();
      return true;
    }
  }

  std::cout << "Movie not found" << std::endl;
  return false;
}

bool MovieStore::borrowMovie(Customer *customer, Movie *movie) {
  // Check if the customer exists in the customers hash table
  if (!customers.contains(std::to_string(customer->getID()))) {
    // throw runtime error if customer does not exist
    throw std::runtime_error("Customer not found");
  }

  // Check if the genre exists in the inventory hash table
  if (!inventory.contains(movie->getGenre())) {
    // throw runtime error if genre does not exist
    throw std::runtime_error("Genre not found");
  }

  // Decrement the stock of the movie in the inventory
  std::vector<Movie *> &movies = inventory.get(movie->getGenre());
  for (Movie *m : movies) {
    if (m == movie) {
      if (m->getStock() <= 0) {
        std::cout << "Movie is out of stock" << std::endl;
        return false;
      } else {
        m->decreaseStock();
        return true;
      }
    }
  }
  std::cout << "Movie not found" << std::endl;
  return false;
}

void MovieStore::printInventory() {
  // Prints movies in a specific order
  std::vector<Movie *> movies = inventory.get('F');
  for (const Movie *movie : movies) {
    movie->print();
  }

  std::vector<Movie *> movies = inventory.get('D');
  for (const Movie *movie : movies) {
    movie->print();
  }

  std::vector<Movie *> movies = inventory.get('C');
  for (const Movie *movie : movies) {
    movie->print();
  }
}

/**
 * Populates this movieStore objects inventory with movie data from specified
 * file.
 */
void MovieStore::populateInventory(std::string filePath) {
  std::ifstream inputFile;

  // Open the file
  inputFile.open(filePath);

  // Check if the file opened successfully
  if (!inputFile.is_open()) {
    throw std::runtime_error("File cannot be opened");
  }

  std::string data;
  while (inputFile >> data) {
    // Read first char (genre) of data
    char genre = data.at(0);
    MovieFactory *factory = movieFactories.get(genre);
    Movie *movie = factory->makeMovie(data);

    // add movie to inventory
    if (inventory.contains(genre)) {
      inventory.get(genre).push_back(movie);
    } else {
      inventory.insert(genre, std::vector<Movie *>{movie});
    }
  }

  inputFile.close();
}