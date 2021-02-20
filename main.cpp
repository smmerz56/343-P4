//---------------------------------------------------------------------------
// main.cpp
//---------------------------------------------------------------------------
//
// Assumptions:
//   -- This program doesnt create transaction objects for 'I' commands
//   -- This program only holds 13 clients in the hash table. That can be 
//      changed easily in Manager.h
//   -- if the transaction has an invalid media type(not a dvd), the user 
//      is alerted and no transaction object is made and stored in the 
//      clients transaction list
//   -- Using g++ -std=c++11 to complie on Linux 
//---------------------------------------------------------------------------      
using namespace std;
#include <iostream>
#include "manager.h"

int main() {                                    
      
   ifstream infile("data4movies.txt"), infile2("data4customers.txt"), infile3("data4commands.txt"); 
   if(!infile){
      cout << "infile not open" << endl;                               
      return 1;       
   }       
   if(!infile2){ 
      cout << "infile2 not open" << endl;                                                  
      return 1;
   } 
   if(!infile3){ 
      cout << "infile3 not open" << endl;                       
      return 1; 
   }           
    
   Manager movieStore(infile, infile2, infile3);   
     
   return 0; 
}
