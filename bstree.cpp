// BSTree class: A Tree made up of Movie objects and their data

#include "bstree.h"
#include "movie.h"
using namespace std;
// --------------------------------------------------------------------------
// Constructor 
BSTree::BSTree(){
   root = nullptr;  
}

// --------------------------------------------------------------------------
// Destructor
BSTree::~BSTree(){
   this->makeEmpty();     
}

// --------------------------------------------------------------------------
// retrieve()
// finds the target in the tree and sets the second parameter to the target
bool BSTree::retrieve(const Movie& target, Movie*& moviePtr) const{
   bool success;
   if(root != nullptr){
      success = retrieveHelper(target, moviePtr, root);   
   }
   if(success){
      return true;
   }
   else{
      return false;
   }   
}

// --------------------------------------------------------------------------
// retrieveHelper()
// a recursive function to help find the target for retrieve
bool BSTree::retrieveHelper(const Movie& target, Movie*& moviePtr, Node* current) const{     
   
   if(current == nullptr){
      return false;
   }
    
   if(*current->data == target){ 
      moviePtr = current->data;       
      return true;
   }   

   bool answer = retrieveHelper(target, moviePtr, current->left);
   
   if(answer){
      return true;
   }
   bool answer2 = retrieveHelper(target, moviePtr, current->right);  
   
   return answer2;  
   
}

// --------------------------------------------------------------------------
// makeEmpty()
// empty the tree, deallocate all memory for all the nodes and each object
void BSTree::makeEmpty(){ 
   if(root != nullptr){
      makeEmptyHelper(root);
   }  
   root = nullptr;
}
// --------------------------------------------------------------------------
// makeEmptyHelper()
// recursive function that assists makeEmpty()
void BSTree::makeEmptyHelper(Node* current){  
   if(current == nullptr){
      return; 
   }
   makeEmptyHelper(current->left);
   makeEmptyHelper(current->right);
   delete current->data;// this takes errors away
   current->data = nullptr;
   delete current;
}
// --------------------------------------------------------------------------
// isEmpty()
// check to see if Tree is empty as defined by a nullptr head
bool BSTree::isEmpty()const{
   return root == nullptr;
}
// --------------------------------------------------------------------------
// insert
// create a Node, attach a Movie to the Node and insert into Tree 
bool BSTree::insert(Movie* dataptr){
   Node* ptr = new Node;
   if (ptr == NULL) return false;            // out of memory
   ptr->data = dataptr;
   ptr->left = ptr->right = NULL;
   if (isEmpty()) {
      root = ptr;
   }
   else {
      Node* current = root;                           // walking pointer
      bool inserted = false;                          // whether inserted yet

      // if item is less than current item, insert in left subtree,
      // otherwise insert in right subtree
      while (!inserted) {
         if (*ptr->data < *current->data) {
            if (current->left == NULL) {              // insert left
               current->left = ptr;
               inserted = true;
            }
            else
               current = current->left;               // one step left
         }
         if (*current->data < *ptr->data){
            if (current->right == NULL) {             // insert right
               current->right = ptr;
               inserted = true;
            }
            else
               current = current->right;              // one step right
         }
         // if the movie being inserted has the same title as one already
         // inserted(classic), compare actors to see where to insert
         if(*ptr->data == *current->data){
            
            if(ptr->data->getActor() < current->data->getActor()){
               
               if (current->left == NULL) {              // insert left                  
                  current->left = ptr;
                  inserted = true;
               }
               else{
                  current = current->left;                  
               }
            }
            else{
               if (current->right == NULL) {             // insert right
                  current->right = ptr;
                  inserted = true;
               }
               else{
                  current = current->right;                  
               }
            }
         }
      }
   }
   return true;   
}

