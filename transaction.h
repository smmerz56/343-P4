#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <fstream>
#include <iostream>
#include <string>
using namespace std; 
//---------------------------------------------------------------------------
// The Transaction class is the parent class to the Borrow, Return and 
// History classes
//---------------------------------------------------------------------------
class Transaction{
public:
   Transaction();
   virtual ~Transaction();
   virtual void setData(int, ifstream&);
   virtual void display();
   //getters
   virtual string getMovieTitle() const;
   virtual int getYear() const;
   virtual string getDirector() const;
   virtual string getActor() const;
   virtual char getMovieGenre() const; 
   
protected:
friend class Manager;
   char type;//borrow, history or return
   int customerNumber;
};
#endif