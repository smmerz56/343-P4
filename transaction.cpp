#include "transaction.h"

// ---------------------------------------------------------------------------
//constructor
Transaction::Transaction(){}

// ---------------------------------------------------------------------------
//destructor 
Transaction::~Transaction(){}      

// ---------------------------------------------------------------------------
//setData
//sets the data from a text file
void Transaction::setData(int accountNumber, ifstream& infile){    
   customerNumber = accountNumber; 
}

// ---------------------------------------------------------------------------
//display
void Transaction::display(){
   cout << type << " " << customerNumber << endl;
}
// ---------------------------------------------------------------------------
//getMovieTitle
//Just for inheritance
string Transaction::getMovieTitle() const{
   return "None";
}
// ---------------------------------------------------------------------------
//getYear
//Just for inheritance
int Transaction::getYear() const{
   return -1;
}
// ---------------------------------------------------------------------------
//getDirector
//Just for inheritance
string Transaction::getDirector() const{
   return "None";
}
// ---------------------------------------------------------------------------
//getActor
//Just for inheritance
string Transaction::getActor() const{
   return "None";
}
// ---------------------------------------------------------------------------
//getMovieGenre
//Just for inheritance
char Transaction::getMovieGenre() const{
   return 'X';
}