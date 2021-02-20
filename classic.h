#ifndef CLASSIC_H
#define CLASSIC_H
#include <string>
#include "movie.h"
#include "transaction.h"

//---------------------------------------------------------------------------
// Classic class inherits from the Movie class
//---------------------------------------------------------------------------

class Classic: public Movie{ 
public:

   Classic();
   ~Classic();
   
   bool equals(Transaction*) const;//compare a Movie with a Transaction
   bool setData(char, ifstream&);//set data from a file
   void displayMovie();
   
   //getter
   string getActor() const;

private:
   friend class Manager;
   string actor;
   int month;
};
#endif