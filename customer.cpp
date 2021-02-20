#include "customer.h"  

using namespace std;

// ---------------------------------------------------------------------------
//constructor 
Customer::Customer(){ 
   lastName = "";
   firstName = "";
   number = 0;
}
// ---------------------------------------------------------------------------
//destructor
Customer::~Customer(){}

// ---------------------------------------------------------------------------
//setData
// sets the data from a file
void Customer::setData(ifstream& infile){    
   infile >> number >> lastName >> firstName;   
    
}

// ---------------------------------------------------------------------------
//getNumber
int Customer::getNumber(){
   return number;
}
// ---------------------------------------------------------------------------
//getFirstName
string Customer::getFirstName(){
   return firstName;
}