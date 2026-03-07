/**
 * Main driver program for the movie store system.
 *
 * This program starts the tests that verifies
 * the functionality of the movie store.
 */

#include <iostream>

using namespace std;

// forward declaration, implementation in store_test.cpp
void testAll();

// main function to run the tests
int main() {

  // Run all movie store tests
  testAll();

  cout << "Done!" << endl;
  return 0;
}
