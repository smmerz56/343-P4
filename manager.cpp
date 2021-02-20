#include "manager.h"
#include "classic.h"
#include "drama.h"
#include "comedy.h"
#include "customer.h" 
using namespace std; 

// ---------------------------------------------------------------------------
//default constructor
Manager::Manager(){} 

// ---------------------------------------------------------------------------
//constructor
Manager::Manager(ifstream& infile, ifstream& infile2, ifstream& infile3){
   for(int i = 0; i < MAXMOVIES; i++){
      customerHashTable[i] = nullptr; 
      comedyMovies[i] = nullptr;
      dramaMovies[i] = nullptr;
      classicMovies[i] = nullptr;
   }
   for(int i = 0; i < MAXCUSTOMERS; i++){
      customerHashTable[i] = nullptr;       
   }
   //inventory, list and commands auto launched from constructor
   createInventory(infile);   
   createCustomerList(infile2);
   processCommands(infile3);
} 

// ---------------------------------------------------------------------------
//destructor
Manager::~Manager(){
   for(int i = 0; i < MAXCUSTOMERS; i++){
      delete customerHashTable[i]; 
   }   
}

// ---------------------------------------------------------------------------
//createInventory
// creates the movie tree and arrays from a file
void Manager::createInventory(ifstream& infile){
   Movie* movie;
   char type;
   string line;
   
   infile >> type; 
   while(!infile.eof()){         
      switch(type){
         case 'F':      
            movie = new Comedy; 
            movie->setData(type, infile); 
            inventory.insert(movie);             
            break;
         case 'D':      
            movie = new Drama; 
            movie->setData(type, infile); 
            inventory.insert(movie);            
            break;
         case 'C':      
            movie = new Classic; 
            movie->setData(type, infile); 
            inventory.insert(movie);            
            break;
         default:// if there is an invalid code
            getline(infile, line);//if invalid code, read in and store 
                           //the rest of the line and display to user
            cout << "Invalid movie genre " << type << line << endl;            
            break;
      }
      infile >> type; 
           
   }
   BSTree::Node* current = inventory.root; // root of tree
   printInventoryHelper(current);// create arrays Movie arrays for printing
   bubbleSort(dramaMovies, 'D');//sort arrays
   bubbleSort(classicMovies, 'C');
}

// ---------------------------------------------------------------------------
//createCustomerList
// create a customer hash table from a file
void Manager::createCustomerList(ifstream& infile){
   int cell = -1;   
   Customer* ptr;
   //loop until eof
   for(;;){
      ptr = new Customer;// create new customer
      ptr->setData(infile);      
      
      if(infile.eof()) {//if eof is reached      
         delete ptr;
         break;
      }
      
      cell = ptr->getNumber() % 10;// find which cell in hash table to 
                                                   //place the customer
      
      // if a collision use linear probing to find where to place the customer
      while(customerHashTable[cell] != nullptr){
         if(cell == MAXCUSTOMERS - 1){
            cell = 0;
         }
         else{
            cell++;      
         }
      }
      
      customerHashTable[cell] = ptr;//asssign the customer to the cell   
   }   
  
}

// ---------------------------------------------------------------------------
//printInventory
// Uses 3 arrays of Movie pointers(comedy, drama, classics) to 
// point to the correct movie type in the tree, then prints each array. 
void Manager::printInventory(){
   int cell = 0;
   
   while(comedyMovies[cell] != nullptr){
      comedyMovies[cell]->displayMovie();
      cell++;
   }
   cell = 0;
   while(dramaMovies[cell] != nullptr){
      dramaMovies[cell]->displayMovie();
      cell++;
   }
   cell = 0;
   while(classicMovies[cell] != nullptr){
      classicMovies[cell]->displayMovie();
      cell++;
   }
}

// ---------------------------------------------------------------------------
//printInventoryHelper
// Traverses the Inventory tree and calls outputArrayLoader() to find which
// Movie array to attach the current movie in the tree to.
void Manager::printInventoryHelper(BSTree::Node* current){ //dereference ptr
   
   if(current == nullptr){
      return;
   }   
   
   printInventoryHelper(current->left);
   outputArrayLoader(current);   
   printInventoryHelper(current->right); 
}

// ---------------------------------------------------------------------------
//printInventoryHelper
// Find which array to use to point to the current movie in the tree.
void Manager::outputArrayLoader(BSTree::Node* current){ 
   int cell = 0;
   // Comedy movie array
   if(current->data->type == 'F'){
      while(comedyMovies[cell] != nullptr){
         cell++;
      }
      comedyMovies[cell] = current->data;
   }
   // Classic movie array
   else if(current->data->type == 'C'){
      while(classicMovies[cell] != nullptr){
         cell++;
      }
      classicMovies[cell] = current->data; 
   }
   // Drama movie array
   else if(current->data->type == 'D'){
      while(dramaMovies[cell] != nullptr){
         cell++;
      }
      dramaMovies[cell] = current->data; 
   }
}

// ---------------------------------------------------------------------------
//processCommands
void Manager::processCommands(ifstream& infile){
   char command;
   int accountNumber;
   int cell;// cell in customerHashTable
   char validMedia;//used to tell if the media a dvd or not
   string line;//used if and invald transaction
   bool success;
   Transaction* ptr;
   
   infile >> command;
   
   while(!infile.eof()){ 
          
      if(command == 'I'){// print the inventory
         printInventory();
      }
      else if(command != 'H' && command != 'B' && command != 'R'){
         getline(infile, line);//if invalid code, read in and store the rest  
                                          //of the line and display to user
         cout << "Invalid action code: " << command << line << endl;
      }
      else{
         infile >> accountNumber;
         
         cell = findCustomer(accountNumber);//find customer cell in hashtable
 
         if(cell == -1){
             getline(infile, line);//if invalid code, read in and store the rest  
                                          //of the line and display to user
            cout << "Invalid customer ID: " << accountNumber << line << endl;            
         }
       
         else {
            if(command == 'H'){ // make History object
               ptr = new History(command, accountNumber);
               //insert into customer list
               customerHashTable[cell]->transactionsList.insert(ptr);
               cout <<"Customer Transaction History for ID number: " << 
                                                   accountNumber << endl;
               //print History  
               customerHashTable[cell]->transactionsList.display();              
            }
           else{
               infile >> validMedia;
               //make sure its a dvd, if not print error and dont make object
               if(validMedia != 'D'){                  
                  getline(infile, line);//if invalid code, read in and store 
                                 // the rest of the line and display to user
                  cout << "Invalid media type for transaction: " << command << 
                     " " << accountNumber << " " << validMedia << line << endl;
               }
               else if(command == 'B'){
                 ptr = new Borrow;//make borrow obj
                 ptr->setData(accountNumber, infile);    
                 customerHashTable[cell]->transactionsList.insert(ptr);
                 //find and subtract from movie tree, print errors
                 success = performTransaction(ptr);
                 if(!success){
                    if(ptr->getMovieGenre() == 'C'){
                     cout << "Invald name: ";
                     ptr->display();
                     cout << endl;
                    // delete ptr;
                    }
                    else if(ptr->getMovieGenre() == 'D'){
                      
                     cout << "Invald name: ";
                     ptr->display();
                     cout << endl;
                    // delete ptr;
                    }
                    else if(ptr->getMovieGenre() == 'F'){
                      
                       cout << "Invald name: ";
                       ptr->display();
                       cout << endl;
                      // delete ptr;
                    }

                 }
                /* else{***********************
                    customerHashTable[cell]->transactionsList.insert(ptr);
                 }*/
               }
               else if(command == 'R'){
                  ptr = new Return;// make return obj
                  ptr->setData(accountNumber, infile); 
                  customerHashTable[cell]->transactionsList.insert(ptr);
                 //find and add to movie tree
                 performTransaction(ptr);
               }  
            
            }        
         }        
        
      }      
      infile >> command;
   }
   
}
// ---------------------------------------------------------------------------
//performTransaction
// performs an individual transaction on the Movie tree
bool Manager::performTransaction(Transaction* ptr){
   char type = ptr->getMovieGenre();
   int cell = 0;
   int cellBack = 0;
   int cellFront = 0;
   bool found = false;   
      
   if(type == 'D'){// if the transaction is a drama
      while(dramaMovies[cell] != nullptr){
         if(dramaMovies[cell]->equals(ptr)){ 

            if(ptr->type == 'R'){//perform return transaction
               dramaMovies[cell]->stock += 1;
               found = true;
               return found;
            }
            else if(ptr->type == 'B'){//perform borrow transaction
               if(dramaMovies[cell]->stock > 0){
                  dramaMovies[cell]->stock -= 1;
                  found = true;
                  return found;
               }
               else{//if not enough to borrow
                  cout << "Not enough in stock for movie: " << 
                                          ptr->getMovieTitle() << endl;
                  return true;
               }
            }            
         }
         else{
            cell++;
         }
      }
   }
   else if(type == 'C'){// if the transaction is a classic
      
      while(classicMovies[cell] != nullptr){
         
         if(classicMovies[cell]->equals(ptr)){ 
            
            if(ptr->type == 'R'){//perform return transaction
               classicMovies[cell]->stock += 1;
               found = true;
               return found;
            }
            else if(ptr->type == 'B'){//perform borrow transaction
          
               if(classicMovies[cell]->stock > 0){
                  classicMovies[cell]->stock -= 1;
                  found = true;
                  return found;
               }
               else{//if classic movie doesnt have enough to borrow, look
                                                         // for more copies
                  
                  cellBack = cell - 1;//used to find other copies
                  cellFront = cell + 1;
                  
                  if(cell != 0 && classicMovies[cellBack]->getReleaseDate() 
                  == ptr->getYear() && classicMovies[cellBack]->stock > 0){                     
                     classicMovies[cellBack]->stock -= 1;
                     found = true;
                     return found;
                  }                 
                  else if(classicMovies[cellFront]->getReleaseDate() == 
                  ptr->getYear() && classicMovies[cellFront]->stock > 0){                     
                     classicMovies[cellFront]->stock -= 1;
                     found = true;
                     return found;
                  }
                  else{
                     cout << "Not enough in stock for the movie staring: " 
                     << ptr->getActor() << " from " << ptr->getYear() << endl; 
                     return true;
                  }
               }
            }
         }
         else{            
            cell++;// advance cell if movie isnt at current cell
         }
      }
   }
   else if(type == 'F'){// if the transaction is a comedy
      
      while(comedyMovies[cell] != nullptr){
         
         if(comedyMovies[cell]->equals(ptr)){ 
             
            if(ptr->type == 'R'){//perform return transaction
               comedyMovies[cell]->stock += 1;
               found = true;
               return found;
            }
            else if(ptr->type == 'B'){//perform borrow transaction
               if(comedyMovies[cell]->stock > 0){
                  comedyMovies[cell]->stock -= 1;
                  found = true;
                  return found;
               }
               else{//if not enough to borrow
                  cout << "Not enough in stock for movie: " << 
                                          ptr->getMovieTitle() << endl;
                  return true;
               }
            }
         }
         else{
            cell++;
         }
      }
   }
   return found;
}

// ---------------------------------------------------------------------------
//findCustomer
// Finds the customer in the hashtable and returns the cell number
int Manager::findCustomer(int accountNumber){
   int originalCell = accountNumber % 10;// to keep track of where in the 
                                       // hashtable the traversing started
   int cell = originalCell;
   
   for(;;){
      if(customerHashTable[cell]->getNumber() == accountNumber){//found cust
         return cell;
      }
      else{// there was a collision or a potential invalid customer ID
        
         if(cell == MAXCUSTOMERS - 1){//if the end of the hashtable has 
                                    //been reached, start at the beginning
            cell = 0;
         }
         else{
            cell++;//advance cell        
         }                
         
         if(cell == originalCell){// went through the entire hashtable,
                                                //not a legit customer ID
            break;
         }
         
      }   
   }
   return -1;
}

//-----------------------------------------------------------------------------
// bubblesort
// Sort array (first parameter) into ascending order by id number; second
// parameter is number of elements considered in the array.
// Algorithm compares consecutive elements and swaps when out of order.

void Manager::bubbleSort(Movie* movies[], char type) { 
   int pass = 0;                            // counts each pass of the sort
   bool done = false;  // whether sorted or not 
   int size = findArraySize(type);   
   // each pass puts one element into its sorted position,
   // smallest value bubbles to the top of the array
   if(type == 'D'){//sorts dramas
      while (!done) {
         done = true;                                 // possibly sorted
         
         // compare consecutive elements, swap if out of order
         for (int i = size - 1; i > pass; i--) {
            
            if (movies[i]->getDirector() < movies[i-1]->getDirector()) {
               
               swap(movies[i], movies[i-1]);
               done = false;                          // still not sorted
            }
         }
         pass++;
      }   
   }
   else{//sorts classics
      while (!done) {
         done = true;                                 // possibly sorted

         // compare consecutive elements, swap if out of order
         for (int i = size - 1; i > pass; i--) {
            if (movies[i]->getReleaseDate() < movies[i-1]->getReleaseDate()) {
               swap(movies[i], movies[i-1]);
               done = false;                          // still not sorted
            }
         }
         pass++;
      }   
   }
}

//-----------------------------------------------------------------------------
// findArraySize
//Since the movie arrays has 101 cells, this function finds how many movie 
// pointer it holds and returns it back to bubblesort
int Manager::findArraySize(char type){
   int size = 0;
   if(type == 'D'){
      while(dramaMovies[size] != nullptr){
         size++;
      }   
   }
   else{
      while(classicMovies[size] != nullptr){
         size++;
      } 
   }
   return size;
}