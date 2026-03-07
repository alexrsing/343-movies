#include "MovieStore.h"
#include <algorithm>
#include <fstream>

// Returns the static movie factory registry
std::map<char, MovieFactoryEntry> &MovieStore::getMovieRegistry() {
  static std::map<char, MovieFactoryEntry> registry;
  return registry;
}

/**
 * Returns the static registry for command factories.
 */
std::map<char, CommandFactory *> &MovieStore::getCommandRegistry() {
  static std::map<char, CommandFactory *> registry;
  return registry;
}

/**
 * Registers a movie factory in the static registry with the given code and
 * priority.
 */
void MovieStore::registerMovieFactory(char code, int priority,
                                      MovieFactory *factory) {
  getMovieRegistry()[code] = {priority, factory};
}

/**
 * Registers a command factory in the static registry with the given code.
 */
void MovieStore::registerCommandFactory(char code, CommandFactory *factory) {
  getCommandRegistry()[code] = factory;
}

/**
 * Constructor for MovieStore. Initializes the movie and command factories from
 * the static registries, and sets up the media types.
 */
MovieStore::MovieStore() {
  // Copy movie factories from static registry, sorted by priority
  std::vector<std::pair<int, char>> ordered;
  for (const auto &entry : getMovieRegistry()) {
    ordered.push_back({entry.second.priority, entry.first});
  }
  std::sort(ordered.begin(), ordered.end());

  // Insert movie factories in priority order
  for (const auto &p : ordered) {
    char code = p.second;
    MovieFactory *factory = getMovieRegistry()[code].factory;
    movieFactories.insert(code, factory);
    genres.push_back(code);
  }

  // Copy command factories from static registry
  for (const auto &entry : getCommandRegistry()) {
    commandFactories.insert(entry.first, entry.second);
  }

  // Register media types
  mediaTypes.push_back('D');
}

MovieStore::~MovieStore() {
  // Delete movies in inventory
  for (const auto &movies : inventory.values()) {
    for (Movie *m : movies) {
      delete m;
    }
  }
  // Delete customers
  for (Customer *c : customers.values()) {
    delete c;
  }
  // Delete commands
  for (Command *cmd : commands) {
    delete cmd;
  }
  // Delete factories in static registries
  for (auto &entry : getMovieRegistry()) {
    delete entry.second.factory;
  }
  getMovieRegistry().clear();
  for (auto &entry : getCommandRegistry()) {
    delete entry.second;
  }
  getCommandRegistry().clear();
}

/**
 * Returns true if the movie was successfully returned by the customer, false
 * otherwise.
 * Increases stock for the returned movie.
 */
bool MovieStore::returnMovie(Customer *customer, Movie *movie) {
  // Check if the customer exists in the customers hash table
  if (!customers.contains(customer->getID())) {
    throw std::runtime_error("Customer not found");
  }

  // Check if the movie exists in the inventory hash table
  if (!inventory.contains(movie->getGenre())) {
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

/**
 * Returns true if the movie was successfully borrowed by the customer,
 * otherwise false.  Decreases stock if movie is available.
 */
bool MovieStore::borrowMovie(Customer *customer, Movie *movie) {
  // Check if the customer exists in the customers hash table
  if (!customers.contains(customer->getID())) {
    throw std::runtime_error("Customer not found");
  }

  // Check if the genre exists in the inventory hash table
  if (!inventory.contains(movie->getGenre())) {
    throw std::runtime_error("Genre not found");
  }

  // Decrement the stock of the movie in the inventory
  std::vector<Movie *> &movies = inventory.get(movie->getGenre());
  for (Movie *m : movies) {
    if (m == movie) {
      if (m->getStock() <= 0) {
        std::cout << "==========================" << std::endl;
        std::cout << customer->getLastName() << " " << customer->getFirstName()
                  << " could NOT borrow " << movie->getTitle()
                  << ", out of stock: " << std::endl;
        std::cout << "==========================" << std::endl;
        return false;
      }

      m->decreaseStock();
      return true;
    }
  }
  std::cout << "Movie not found" << std::endl;
  return false;
}

/**
 * Prints the inventory of movies in the store, sorted by genre and then by
 * movie
 */
void MovieStore::printInventory() {
  for (char genre : genres) {
    if (inventory.contains(genre)) {
      for (const Movie *movie : inventory.get(genre)) {
        movie->print();
      }
    }
  }
}

/**
 * Populates the inventory of movies from a file.
 */
void MovieStore::populateInventory(std::string filePath) {
  std::ifstream inputFile;

  inputFile.open(filePath);

  if (!inputFile.is_open()) {
    throw std::runtime_error("File cannot be opened");
  }

  std::string data;
  while (std::getline(inputFile, data)) {
    if (data.empty()) {
      continue;
    }
    char genre = data.at(0);

    if (!movieFactories.contains(genre)) {
      std::cout << "Unknown movie type: " << genre
                << ", discarding line: " << data.substr(1) << std::endl;
      continue;
    }
    MovieFactory *factory = movieFactories.get(genre);
    Movie *movie = factory->makeMovie(data);

    if (inventory.contains(genre)) {
      inventory.get(genre).push_back(movie);
    } else {
      inventory.insert(genre, std::vector<Movie *>{movie});
    }
  }

  inputFile.close();

  for (char genre : genres) {
    if (inventory.contains(genre)) {
      std::sort(inventory.get(genre).begin(), inventory.get(genre).end(),
                [](const Movie *a, const Movie *b) { return *b > *a; });
    }
  }
}

/**
 * Populates the customers from a file.
 */
void MovieStore::populateCustomers(std::string filePath) {
  std::ifstream inputFile;

  inputFile.open(filePath);

  if (!inputFile.is_open()) {
    throw std::runtime_error("File cannot be opened");
  }

  std::string data;
  while (std::getline(inputFile, data)) {
    if (data.empty()) {
      continue;
    }
    Customer *customer = CustomerFactory::makeCustomer(data);
    customers.insert(customer->getID(), customer);
  }

  inputFile.close();
}

/**
 * Returns a pointer to the customer with the given ID
 */
Customer *MovieStore::getCustomer(int id) {
  if (!customers.contains(id)) {
    return nullptr;
  }
  return customers.get(id);
}

std::vector<Movie *> &MovieStore::getMovies(char genre) {
  try {
    return inventory.get(genre);
  } catch (const std::runtime_error &e) {
    static std::vector<Movie *> empty;
    return empty;
  }
}

/**
 * Returns true if the given media type is valid for this store, false
 * otherwise.
 */
bool MovieStore::validMediaType(char type) const {
  return std::any_of(mediaTypes.begin(), mediaTypes.end(),
                     [type](char mt) { return mt == type; });
}

// Load data from files
void MovieStore::populateCommands(std::string filePath) {
  std::ifstream inputFile;

  inputFile.open(filePath);

  if (!inputFile.is_open()) {
    throw std::runtime_error("File cannot be opened");
  }

  std::string data;
  while (std::getline(inputFile, data)) {
    if (data.empty()) {
      continue;
    }
    char commandType = data.at(0);
    if (!commandFactories.contains(commandType)) {
      std::cout << "Unknown command type: " << commandType
                << ", discarding line: " << data.substr(1) << std::endl;
      continue;
    }
    CommandFactory *factory = commandFactories.get(commandType);
    Command *command = factory->createCommand(data, this);
    if (command == nullptr) {
      continue;
    }
    commands.push_back(command);
  }

  inputFile.close();
}

// Execute all commands in the order they were read from the file
void MovieStore::executeCommands() {
  for (Command *cmd : commands) {
    cmd->execute();
  }
}
