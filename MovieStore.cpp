#include "MovieStore.h"
#include <fstream>

bool MovieStore::returnMovie(Customer *customer, Movie *movie) {
  // Check if the customer exists in the customers hash table
  if (!customers.contains(customer->getID())) {
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
  if (!customers.contains(customer->getID())) {
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
      }

      m->decreaseStock();
      return true;
    }
  }
  std::cout << "Movie not found" << std::endl;
  return false;
}

void MovieStore::printInventory() {
  // Prints movies in a specific order
  std::vector<Movie *> fMovies = inventory.get('F');
  for (const Movie *movie : fMovies) {
    movie->print();
  }

  std::vector<Movie *> dMovies = inventory.get('D');
  for (const Movie *movie : dMovies) {
    movie->print();
  }

  std::vector<Movie *> cMovies = inventory.get('C');
  for (const Movie *movie : cMovies) {
    movie->print();
  }
}

/**
 * Populates this movieStore object inventory with movie data from specified
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

    if (!movieFactories.contains(genre)) {
      continue;
    }
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

/**
 * Populates this movieStore object customers with movie data from specified
 * file.
 */
void MovieStore::populateCustomers(std::string filePath) {
  std::ifstream inputFile;

  // Open the file
  inputFile.open(filePath);

  // Check if the file opened successfully
  if (!inputFile.is_open()) {
    throw std::runtime_error("File cannot be opened");
  }

  std::string data;
  while (inputFile >> data) {
    Customer *customer = CustomerFactory::makeCustomer(data);
    customers.insert(customer->getID(), customer);
  }

  inputFile.close();
}

/**
 * Populates this movieStore object commands with movie data from specified
 * file.
 */
Customer *MovieStore::getCustomer(int id) {
  if (!customers.contains(id)) {
    return nullptr;
  }
  return customers.get(id);
}

std::vector<Movie *> &MovieStore::getMovies(char genre) {
  return inventory.get(genre);
}

void MovieStore::populateCommands(std::string filePath) {
  std::ifstream inputFile;

  // Open the file
  inputFile.open(filePath);

  // Check if the file opened successfully
  if (!inputFile.is_open()) {
    throw std::runtime_error("File cannot be opened");
  }

  std::string data;
  while (inputFile >> data) {
    char commandType = data.at(0);
    // confirm that command type exists in commandFactories hash table - discard
    // line if doesn't exist
    if (!commandFactories.contains(commandType)) {
      continue;
    }
    CommandFactory *factory = commandFactories.get(commandType);
    Command *command = factory->createCommand(data, this);
    commands.insert(commandType, command);
  }

  inputFile.close();
}