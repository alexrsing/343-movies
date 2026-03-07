# Self-Evaluation

## Name(s): Alex Sing, Roshia Dutta

Out of 25 points. Use output.txt created using
`./run-full.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes

- If the program does not compile or gives a segmentation error when run,
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: 75

- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: Full
History: Full
Borrow: Full
Return: Full


Q: -1 for each compilation warning, min -3: 0

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: 0

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: 0

- Check under *4. clang-format does not find any formatting issues*


Q: -2 for any detected memory leak: 0

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: 0

- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documents (min -3): 0

- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: Class: MovieStore.cpp, Method: populateCommands

invalid movie type: MovieStore.cpp, Method: populateInventory

invalid customer ID: BorrowCommandFactory::createCommand, ReturnCommandFactory::createCommand, HistoryCommandFactory::createCommand

invalid movie: BorrowCommandFactory::createCommand, ReturnCommandFactory::createCommand. When a movie does not match any movies in the inventory, 

factory classes: ClassicMovieFactory, ComedyMovieFactory, DramaMovieFactory, CustomerFactory, BorrowCommandFactory, ReturnCommandFactory, HistoryCommandFactory, InventoryCommandFactory

hashtable: A template hash table is used in MovieStore to store movies (inventory), movie factories, commands, command factories, and customers. THe underlying data structure is a vector<std::list<HashNode>> with 101 buckets (HashNode lists). 

container used for comedy movies: std::vector<Movie*> stored in MyHashTable<char, std::vector<Movie*>> inventory keyed by 'F'

function for sorting comedy movies: All movies are sorted in MovieStore::populateInventory. Once the HashTable is populated, each vector (one for each genre) is sorted using std::sort. Comedy movies are sorted by title, then year.

function where comedy movies are sorted: MovieStore::populateInventory

functions called when retrieving a comedy movie based on title and year: MovieStore::getMovies('F') -> Comedy::isEqual(const std::string&)

functions called for retrieving and printing customer history: HistoryCommandFactory::createCommand -> MovieStore::getCustomer -> HistoryCommand::execute -> Customer::printTransactions

container used for customer history: std::vector<std::pair<char, Movie*>> - a vector of pairs of command char to Movie*

functions called when borrowing a movie: BorrowCommandFactory::createCommand creates the borrow command -> BorrowCommand::execute -> MovieStore::borrowMovie -> Customer::addTransaction

explain borrowing a movie that does not exist: In BorrowCommandFactory::createCommand, before the BorrowCommand is created, the system checks if the movie is a valid movie. If not, it prints "Invalid borrow command data" and a nullptr is returned and nothing is added to the commands.

explain borrowing a movie that has 0 stock: In MovieStore::borrowMovie, it prints {title} is out of stock if stock <= 0

explain returning a movie that customer has not checked out: When a customer tries to return a movie, a check is done to see if the customer currently has the movie checked out. This is done by checking in the customers transaction history if borrow count for the movie is greater than return count

any static_cast or dynamic_cast used: Classic::isEqual, Classic::operator>, Comedy::isEqual, Comedy::operator>, Drama::isEqual, Drama::operator>

## Bonus +5

Are there multiple files, of the form runit-without-XXX, where the same set of files will compile and run excluding some of the commands or genres? Yes




Q: Total points: ADD_ALL_POINTS (max 25 (+ 5 Bonus)) 30