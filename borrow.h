#ifndef BORROW_H
#define BORROW_H
#include "transaction.h"
#include <fstream>
#include <string>

//---------------------------------------------------------------------------
// Borrow class inherits from Transaction class
//---------------------------------------------------------------------------
using namespace std;

class Borrow: public Transaction{
public:
   Borrow();
   ~Borrow();
   
   void setData(int, ifstream&);
   void display();
   //getters
   string getMovieTitle() const;
   int getYear() const;
   string getDirector() const;
   string getActor() const;
   char getMovieGenre() const;
   
private: 
   char mediaType;
   char movieGenre; 
   string movieTitle;
   int month;
   int year;
   string director;
   string actor;
};
#endif