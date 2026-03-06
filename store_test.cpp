/**
 * Testing ass4 movie store functions
 *
 * @author Yusuf Pisan
 * @date 19 Jan 2019
 */

#include "MovieStore.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

void testStore1() {
  cout << "Start testStore1" << endl;
  // Should do something more, but lets just read files
  // since each implementation will
  string cfile = "testcommands-1.txt";
  stringstream out;
  ifstream fs(cfile);
  assert(fs.is_open());
  char commandType;
  string discard;
  while (fs >> commandType) {
    out << commandType;
    getline(fs, discard);
  }
  fs.close();
  string result = "IHHBRIBBIH";
  assert(out.str() == result);
  cout << "End testStore1" << endl;
}

void testStore2() {
  cout << "Start testStore2" << endl;
  MovieStore store;

  // Test populateInventory
  store.populateInventory("data4movies.txt");

  // Verify comedies (genre 'F') loaded
  vector<Movie *> &comedies = store.getMovies('F');
  assert(!comedies.empty());
  assert(comedies.size() == 8);

  // Verify dramas (genre 'D') loaded
  vector<Movie *> &dramas = store.getMovies('D');
  assert(!dramas.empty());
  assert(dramas.size() == 8);

  // Verify classics (genre 'C') loaded
  vector<Movie *> &classics = store.getMovies('C');
  assert(!classics.empty());
  assert(classics.size() == 14);

  // Test populateCustomers
  store.populateCustomers("data4customers.txt");

  // Verify known customers exist
  Customer *wally = store.getCustomer(8000);
  assert(wally != nullptr);
  assert(wally->getID() == 8000);

  Customer *minnie = store.getCustomer(1000);
  assert(minnie != nullptr);
  assert(minnie->getID() == 1000);

  Customer *mickey = store.getCustomer(1111);
  assert(mickey != nullptr);
  assert(mickey->getID() == 1111);

  // Non-existent customer returns nullptr
  assert(store.getCustomer(1234) == nullptr);
  assert(store.getCustomer(0) == nullptr);

  // Test borrowMovie and returnMovie directly
  Movie *youveGotMail = nullptr;
  for (Movie *m : comedies) {
    if (m->isEqual(string(" You've Got Mail, 1998"))) {
      youveGotMail = m;
      break;
    }
  }
  assert(youveGotMail != nullptr);
  assert(youveGotMail->getStock() == 10);

  // Borrow and verify stock decreases
  assert(store.borrowMovie(wally, youveGotMail) == true);
  assert(youveGotMail->getStock() == 9);

  // Return and verify stock increases
  assert(store.returnMovie(wally, youveGotMail) == true);
  assert(youveGotMail->getStock() == 10);

  // Test isEqual for dramas
  Movie *gmv = nullptr;
  for (Movie *m : dramas) {
    if (m->isEqual(string(" Barry Levinson, Good Morning Vietnam,"))) {
      gmv = m;
      break;
    }
  }
  assert(gmv != nullptr);
  assert(gmv->getTitle() == "Good Morning Vietnam");

  // Test isEqual for classics
  Movie *haroldAndMaude = nullptr;
  for (Movie *m : classics) {
    if (m->isEqual(string(" 3 1971 Ruth Gordon"))) {
      haroldAndMaude = m;
      break;
    }
  }
  assert(haroldAndMaude != nullptr);
  assert(haroldAndMaude->getStock() == 10);

  // Test populateCommands (exercises all command factories)
  store.populateCommands("data4commands.txt");

  // Print inventory
  store.printInventory();

  cout << "End testStore2" << endl;
}

void testStoreFinal() {
  cout << "=====================================" << endl;
  cout << "Start testStoreFinal" << endl;
  MovieStore store;
  store.populateInventory("data4movies.txt");
  store.populateCustomers("data4customers.txt");

  // Test Movie getters
  vector<Movie *> &comedies = store.getMovies('F');
  Movie *annieHall = nullptr;
  for (Movie *m : comedies) {
    if (m->isEqual(string(" Annie Hall, 1977"))) {
      annieHall = m;
      break;
    }
  }
  assert(annieHall != nullptr);
  assert(annieHall->getTitle() == "Annie Hall");
  assert(annieHall->getDirector() == "Woody Allen");
  assert(annieHall->getGenre() == 'F');
  assert(annieHall->getYear() == 1977);
  assert(annieHall->getStock() == 10);
  assert(annieHall->isAvailable() == true);

  // Test transaction history: borrow then verify
  Customer *porky = store.getCustomer(8888);
  assert(porky != nullptr);
  assert(porky->getTransactions().empty());

  assert(store.borrowMovie(porky, annieHall) == true);
  porky->addTransaction('B', annieHall);
  assert(annieHall->getStock() == 9);

  // Verify transaction was recorded
  auto transactions = porky->getTransactions();
  assert(transactions.size() == 1);
  assert(transactions[0].first == 'B');
  assert(transactions[0].second == annieHall);

  // Return and verify both transactions recorded
  assert(store.returnMovie(porky, annieHall) == true);
  porky->addTransaction('R', annieHall);
  assert(annieHall->getStock() == 10);

  transactions = porky->getTransactions();
  assert(transactions.size() == 2);
  assert(transactions[1].first == 'R');
  assert(transactions[1].second == annieHall);

  // Test out-of-stock: borrow until stock is 0
  Customer *daffy = store.getCustomer(9999);
  assert(daffy != nullptr);
  for (int i = 0; i < 10; i++) {
    assert(store.borrowMovie(daffy, annieHall) == true);
  }
  assert(annieHall->getStock() == 0);
  assert(annieHall->isAvailable() == false);

  // Borrowing when out of stock should fail
  assert(store.borrowMovie(daffy, annieHall) == false);
  assert(annieHall->getStock() == 0);

  // Return one copy, should be available again
  assert(store.returnMovie(daffy, annieHall) == true);
  assert(annieHall->getStock() == 1);
  assert(annieHall->isAvailable() == true);

  // Test isEqual negative cases for comedy
  assert(annieHall->isEqual(string(" Bogus Title, 1977")) == false);
  assert(annieHall->isEqual(string(" Annie Hall, 2000")) == false);

  // Test isEqual negative cases for drama
  vector<Movie *> &dramas = store.getMovies('D');
  Movie *schindlers = nullptr;
  for (Movie *m : dramas) {
    if (m->isEqual(string(" Steven Spielberg, Schindler's List,"))) {
      schindlers = m;
      break;
    }
  }
  assert(schindlers != nullptr);
  assert(schindlers->isEqual(string(" Steven Spielberg, Wrong Title,")) ==
         false);
  assert(schindlers->isEqual(string(" Wrong Director, Schindler's List,")) ==
         false);

  // Test isEqual negative cases for classic
  vector<Movie *> &classics = store.getMovies('C');
  Movie *casablanca = nullptr;
  for (Movie *m : classics) {
    if (m->isEqual(string(" 8 1942 Humphrey Bogart"))) {
      casablanca = m;
      break;
    }
  }
  assert(casablanca != nullptr);
  assert(casablanca->isEqual(string(" 8 1942 Wrong Actor")) == false);
  assert(casablanca->isEqual(string(" 1 1942 Humphrey Bogart")) == false);

  // Test multiple customers borrowing the same movie
  Customer *freddie = store.getCustomer(5000);
  Customer *larry = store.getCustomer(9000);
  assert(freddie != nullptr);
  assert(larry != nullptr);
  assert(store.borrowMovie(freddie, schindlers) == true);
  assert(schindlers->getStock() == 9);
  assert(store.borrowMovie(larry, schindlers) == true);
  assert(schindlers->getStock() == 8);

  cout << "End testStoreFinal" << endl;
  cout << "=====================================" << endl;
}

void testAll() {
  testStore1();
  testStore2();
  testStoreFinal();
}
