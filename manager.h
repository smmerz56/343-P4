#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <fstream>
#include "bstree.h"
#include "movie.h"
#include "classic.h"
#include "drama.h"
#include "comedy.h"
#include "customer.h"
#include "transaction.h"
#include "history.h"
#include "borrow.h"
#include "return.h"

// ---------------------------------------------------------------------------
// Manager class
// -- Creates the Movie BSTree
// -- Creates the Customer Hash Table
// -- Processes the commands 
// ---------------------------------------------------------------------------

using namespace std;

const int MAXMOVIES = 101; 
const int MAXCUSTOMERS = 12;

class Manager{
public:
   Manager();
   Manager(ifstream&, ifstream&, ifstream&);// main constructor
   ~Manager();
   
   void processCommands(ifstream&);
   
private:
   BSTree inventory; // movie inventory
   Customer* customerHashTable[MAXCUSTOMERS];// customer hashtable
   
   void createInventory(ifstream&);//loads the movies into tree
   void createCustomerList(ifstream&);// loads customer objects into hash table
   int findCustomer(int);// finds the customer in the hashtable
   void printInventory(); //prints the movies
   void printInventoryHelper(BSTree::Node*);// helps print the movies
   void outputArrayLoader(BSTree::Node*); //also helps print the movies
   bool performTransaction(Transaction*); //performs a transaction 
   void bubbleSort(Movie*[], char);// sorts the movies for printing
   int findArraySize(char);// used in bubblesort to find the size of the array
   
   Movie* comedyMovies[MAXMOVIES];//comedy movie array of pointers to the BST for printing
   Movie* dramaMovies[MAXMOVIES];//drama movie array of pointers to the BST for printing
   Movie* classicMovies[MAXMOVIES];//classic movie array of pointers to the BST for printing
   
};
#endif