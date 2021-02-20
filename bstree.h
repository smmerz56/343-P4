#ifndef BSTREE_H
#define BSTREE_H

//---------------------------------------------------------------------------
// BSTree to hold movie objects
//---------------------------------------------------------------------------

#include "movie.h"
using namespace std; 

class BSTree{ 
private:
   friend class Manager;
   struct Node { // Tree is made up of Nodes with data pointer to Movie objects 
      Movie* data;
      Node* right; 
      Node* left; 
   }; 
   Node* root; // root of the tree
   public:
   BSTree();
   ~BSTree(); // calls makeEmpty which deallocates all memory
   // insert object into the tree, parameter holds pointer to object to insert
   bool insert(Movie*);

   // retrieve object, first parameter is object to retrieve
   // second parameter holds pointer to found object, nullptr if not found
   bool retrieve(const Movie&, Movie*&) const;
   bool retrieveHelper(const Movie&, Movie*&, Node*) const;
   void display() const; // displays the contents of a tree to cout
   void displayHelper(Node*) const; 
   void makeEmpty();     // empties the current tree, deallocates all memory
   void makeEmptyHelper(Node*);
   bool isEmpty() const; // returns true if tree is empty
};
#endif