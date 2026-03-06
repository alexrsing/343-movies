#include "MovieStore.h"
#include "BorrowCommand.h"
#include "Classic.h"
#include "Comedy.h"
#include "Drama.h"
#include "HistoryCommand.h"
#include "InventoryCommand.h"
#include "ReturnCommand.h"
#include <algorithm>
#include <fstream>

MovieStore::MovieStore() {
  // Register movie factories
  movieFactories.insert('F', new ComedyMovieFactory());
  movieFactories.insert('D', new DramaMovieFactory());
  movieFactories.insert('C', new ClassicMovieFactory());

  // Register command factories
  commandFactories.insert('B', new BorrowCommandFactory());
  commandFactories.insert('R', new ReturnCommandFactory());
  commandFactories.insert('H', new HistoryCommandFactory());
  commandFactories.insert('I', new InventoryCommandFactory());
}

MovieStore::~MovieStore() {
  // Delete movie factories
  for (MovieFactory *f : movieFactories.values()) {
    delete f;
  }
  // Delete command factories
  for (CommandFactory *f : commandFactories.values()) {
    delete f;
  }
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
  for (const auto &cmds : commands.values()) {
    for (Command *cmd : cmds) {
      delete cmd;
    }
  }
}

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
        printf("%s is out of stock\n", m->getTitle().c_str());
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
  while (std::getline(inputFile, data)) {
    if (data.empty()) {
      continue;
    }
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

  for (char genre : {'F', 'D', 'C'}) {
    if (inventory.contains(genre)) {
      std::sort(inventory.get(genre).begin(), inventory.get(genre).end(),
                [](const Movie *a, const Movie *b) { return *b > *a; });
    }
  }
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
  try {
    return inventory.get(genre);
  } catch (const std::runtime_error &e) {
    std::cout << "Genre " << genre << " not found in inventory" << std::endl;
    // if genre does not exist, return empty vector
    static std::vector<Movie *> empty;
    return empty;
  }
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
  while (std::getline(inputFile, data)) {
    if (data.empty()) {
      continue;
    }
    char commandType = data.at(0);
    // confirm that command type exists in commandFactories hash table - discard
    // line if doesn't exist
    if (!commandFactories.contains(commandType)) {
      continue;
    }
    CommandFactory *factory = commandFactories.get(commandType);
    Command *command = factory->createCommand(data, this);
    if (command == nullptr) {
      continue;
    }
    if (commands.contains(commandType)) {
      commands.get(commandType).push_back(command);
    } else {
      commands.insert(commandType, std::vector<Command *>{command});
    }
  }

  inputFile.close();
}