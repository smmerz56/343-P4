#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "list.h"
#include <string>
#include <fstream>
using namespace std;

// ---------------------------------------------------------------------------
//The Customer class stores the info for every customer of the movie store
// ---------------------------------------------------------------------------
 
class Customer {
public:
   Customer();
   ~Customer();
   void setData(ifstream&);
   
   //getters
   int getNumber();
   string getFirstName();
   
private:
   friend class Manager;
   string firstName;
   string lastName;
   int number;
   
   List transactionsList;// List of transaction objects
   
};
#endif