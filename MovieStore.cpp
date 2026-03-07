#include "MovieStore.h"
#include <algorithm>
#include <fstream>

// Static registry accessors
std::map<char, MovieFactoryEntry> &MovieStore::getMovieRegistry() {
  static std::map<char, MovieFactoryEntry> registry;
  return registry;
}

std::map<char, CommandFactory *> &MovieStore::getCommandRegistry() {
  static std::map<char, CommandFactory *> registry;
  return registry;
}

void MovieStore::registerMovieFactory(char code, int priority,
                                      MovieFactory *factory) {
  getMovieRegistry()[code] = {priority, factory};
}

void MovieStore::registerCommandFactory(char code, CommandFactory *factory) {
  getCommandRegistry()[code] = factory;
}

MovieStore::MovieStore() {
  // Copy movie factories from static registry, sorted by priority
  std::vector<std::pair<int, char>> ordered;
  for (const auto &entry : getMovieRegistry()) {
    ordered.push_back({entry.second.priority, entry.first});
  }
  std::sort(ordered.begin(), ordered.end());

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
        std::cout << movie->getTitle() << " is out of stock" << std::endl;
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
  for (char genre : genres) {
    if (inventory.contains(genre)) {
      for (const Movie *movie : inventory.get(genre)) {
        movie->print();
      }
    }
  }
}

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

bool MovieStore::validMediaType(char type) const {
  for (char mt : mediaTypes) {
    if (mt == type) {
      return true;
    }
  }
  return false;
}

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

void MovieStore::executeCommands() {
  for (Command *cmd : commands) {
    cmd->execute();
  }
}
