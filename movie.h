#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <fstream>
#include <iostream>
#include "transaction.h"

using namespace std; 

// ---------------------------------------------------------------------------  
// Movie objects make up the BSTree and Movie arrays in the Manager
// -- The parent class to the Drama, Comedy and Classic classes
// ---------------------------------------------------------------------------  

class Movie{
public:   
   Movie();
   virtual ~Movie(); // destructor

   virtual bool setData(char, ifstream&); // fill Movie with data from file.
   virtual void displayMovie();
   
   //getters   
   virtual string getActor() const;
   string getDirector() const;
   string getTitle() const;
   int getReleaseDate() const;
   
   bool operator<(const Movie&) const;  // to figure out where in the  
                                         // tree to put the Movie.
                                        
   bool operator==(const Movie&) const; // Helps sort the movies in the tree
   virtual bool equals(Transaction*) const; // helps compare the movie with a 
                                                      // Transaction object
   

protected:
   friend class Manager;
   char type;//classic, drama, comedy
   int stock;// how many
   string director;
   string title;
   int releaseDate;
};
#endif