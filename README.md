Description
A local movie rental store wishes to automate their inventory tracking system. Currently there are three types of movies/videos (in DVD media) to be tracked:

Comedy (denoted as ‘F’ for funny)
Drama (denoted as ‘D’)
Classics (denoted as ‘C’)
Borrows and returns of items by customers are also to be tracked. Four types of actions are desired in the system:

Borrow (denoted as ‘B’): (stock – 1) for each item borrowed  
Return (denoted as ‘R’): (stock + 1) for each item returned
Inventory (denoted as ‘I’): outputs the inventory of all the items in the store
History (denoted as ‘H’): outputs all the transactions of a customer 
 

You will design and implement a program that will initialize the contents of the inventory from a file (data4movies.txt), the customer list from another file (data4customers.txt), and then process an arbitrary sequence of commands from a third file (data4commands.txt).

Details
File formats and file details are as follows:

data4movies.txt:

The information about each movie is listed as follows: 

Comedy: F, Stock, Director, Title, Year it released 
Drama: D, Stock, Director, Title, Year it released
Classics: C, Stock, Director, Title, Major actor Release date
For example,

F, 10, Nora Ephron, You've Got Mail, 1998
D, 10, Steven Spielberg, Schindler's List, 1993
C, 10, George Cukor, Holiday, Katherine Hepburn 9 1938
C, 10, George Cukor, Holiday, Cary Grant 9 1938
Z, 10, Hal Ashby, Harold and Maude, Ruth Gordon 2 1971
D, 10, Phillippe De Broca, King of Hearts, 1967

You may assume correct formatting, but codes may be invalid; e.g., in this data, the 'Z' code is an invalid entry so this line has to be discarded and users should be notified about this issue. 
While the stock for each line is 10, do not assume that is the case in your design and implementation.
The movies should be sorted as follows when stored in the system:
Comedy (‘F’) sorted by Title, then Year it released 
Dramas (‘D’) are sorted by Director, then Title 
Classics (‘C’) are sorted by Release date, then Major actor
Each item is uniquely identified by its complete set of sorting attributes.  
The classical movie type has a different format than the other two. 
Major actor is always formatted as two strings, FirstName and LastName, separated by a space.
The Release date contains month and year information, and no comma (but a space) between Major actor and Release date. 
In addition, for classical movies, one movie (e.g., Holiday) may have multiple lines, but since each classical movie is uniquely identified by its sorting attributes (Release date, then Major actor in this case), the two entries are treated as separate movies.
data4customers.txt:

The information about each customer is listed as follows: 

Customer: CustomerID LastName FirstName 
For example,

1111 Mouse Mickey
1000 Mouse Minnie

You may assume that the data is formatted correctly. 
CustomerID is 4-digits and uniquely identifies each customer
data4commands.txt:

The information about each command is listed as follows:

Inventory I
History H CustomerID
Borrow B CustomerID MediaType MovieType (movie sorting attributes)
Return R CustomerID MediaType MovieType (movie sorting attributes)
For example,

B 1234 D C 9 1938 Katherine Hepburn
B 1234 D F Pirates of the Caribbean, 2003
R 1234 D C 9 1938 Katherine Hepburn
B 1234 D D Steven Spielberg, Schindler's List
I
H 1234
X 1234 Z C 9 1938 Katherine Hepburn
B 1234 D Y 2 1971 Ruth Gordon
B 9999 D F Pirates of the Caribbean, 2003
B 1234 D C 2 1975 Blah Blah     

 

You may assume correct formatting, but codes may be invalid. You must handle an invalid command code (e.g., ‘X’ in the above example), invalid movie type (e.g., ‘Y’), invalid customer ID (i.e., not found. For example, 9999), and invalid movie (i.e., not found. For example, classic movie in month 2 of 1975 with a "Blah Blah" title). For bad data, discard the line and notify users.
The MediaType is currently on 'D', but may be expanded in the future.
The B and R commands identify the movie using the two sorting attributes, using comma or space to separate them as in the movie data file.
Comedy: B 1234 D F Pirates of the Caribbean, 2003
Drama: B 1234 D D Steven Spielberg, Schindler's List,
Classics: R 1234 D C 9 1938 Katherine Hepburn
Overall Requirements   
Do not print output for successful ‘B’ or ‘R’ commands, but print error messages for incorrect data and/or incorrect command. 
Output for ‘H’ and ‘I’ commands should be neatly formatted with one line per item/transaction.
‘I’ should output all Comedy movies, then all Dramas, then all Classics. Each category of movies should be ordered according to the sorting criteria discussed above. The data should include how many movies are borrowed and how many remain.
‘H’ should show a list of DVD transactions of a customer in chronological order (1st transaction, 2nd transaction, ....) and specify whether the movie was borrowed or returned. 
You are required to use at least one hash table in this assignment. There are actually multiple places where they could be used. You can use STL map, vector and other data structures, but you must have one hash table that you implement yourself. The hash table you implement does not need to be extensive, minimum features to store key-id pairs and retrieve them in O(1) time is fine.
You must use inheritance and have polymorphic functions. If you find you’re using templates a lot, run it by me, as this assignment is designed for you to practice using inheritance and polymorphism. 
This assignment is to be fully object‐oriented so when you store multiple pieces of information, it would be stored in an object. Strings are only to be used in a primitive sense, for example, one name, one title, one of anything. Do NOT build long strings that hold complex information.
Think about what files would need to be added or modified if a new movie genre, such as horror, was added. Think about what files would need to be modified if a new command, such as number of movies out, was added. If you are using if/else statements for your movie genres or your commands, you are doing it wrong. You must use polymorphism for this assignment.
Good software practice says that each class should get its own .h and .cpp file. For this assignment, you will likely have over 10 classes, so for ease of programming you can put closely related classes into a common .h file (and a common .cpp) file. This is only for very closely related classes.
The structure of your classes and taking advantage of the design patterns is especially important for this assignment. You need to follow the basic design principles, have it extendable, efficient, well-documented, etc.

Review the polymorphism code in https://github.com/pisan343/polymorphismLinks to an external site. especially the code for "poly-pet-factory-self-register". In that example, the code can be compiled with and without the horse.cpp file which will result in different outputs. Similarly, it should be possible to compile your code leaving out any one of the commands or any one of the genres. Anytime you have an if statement (for a command or for a genre), ask yourself whether you can get rid of the conditional by making your code more polymorphic.

Bonus +5: Provide multiple runit-without-XXX.sh files where the same set of files will compile and run excluding some of the commands or genres. This is only possible if you are using self-registration for each data type, command type and have a fully polymorphic design.

