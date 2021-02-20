#include "list.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
//----------------------------------------------------------------------------
// Constructor
// this sets the head node of the newly created list to null
List::List()      
{
   head = nullptr;  
}

//----------------------------------------------------------------------------
// Destructor
// calls makeEmpty to delete everything in the list
List::~List()
{
   makeEmpty();
}

//----------------------------------------------------------------------------
// display()
// displays the Transactions of the List
void List::display()const { 
   Node* current = head;
   
   while(current != nullptr) { 
      current->data->display();
      current = current->next;
   }
   
}


//---------------------------------------------------------------------------
// insert
// inserts a Transaction into the List
void List::insert(Transaction* dataPtr){ 
  
   Node* ptr = new Node;

   ptr->data = dataPtr;   
   
   if(isEmpty()) {       
      ptr->next = head;// says ptr->next = nullptr
      head = ptr;
   } 
   else {
      ptr->next = head;
      head = ptr;      
   }   
}

//---------------------------------------------------------------------------
// isEmpty
// check to see if List is empty as defined by a nullptr head
bool List::isEmpty() const{
   return head == nullptr;
}

//---------------------------------------------------------------------------
// makeEmpty
// empty the list, deallocate all memory for all the nodes and each object
void List::makeEmpty(){
   Node* current = head;
   Node* next;

   while(current != nullptr) {
      next = current->next;
      delete current->data;
      current->data = nullptr;
      delete current;
      current = next;
   }
   head = nullptr;
   current = nullptr;
   next = nullptr;
}