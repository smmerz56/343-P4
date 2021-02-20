#ifndef LIST_H
#define LIST_H

#include "transaction.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;



#include "transaction.h"
//----------------------------------------------------------------------------clTabCtrl
// ADT List:A collection of Transaction objects. A limited functionality List
//
// Assumptions:
//    -- The user will only be using Transaction objects.
//----------------------------------------------------------------------------
class List
{
 
private:   
   // the nodes which make up the list
   struct Node {
      Transaction* data;
      Node* next;
   };
   Node* head;
  
   public:
   // constructors and destructor
   List(); 
   ~List();

   void insert(Transaction*);//insert into List
   void display()const;  

   bool isEmpty() const;
   void makeEmpty();

};

#endif