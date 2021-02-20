#include "classic.h"
using namespace std;

// ---------------------------------------------------------------------------
//constructor
Classic::Classic(){} 

// ---------------------------------------------------------------------------
//destructor
Classic::~Classic(){} 

// ---------------------------------------------------------------------------
//setData
bool Classic::setData(char genre, ifstream& infile){  
   type = genre;
   char character;
   string name;
   infile >> character >> stock >> character;// the character are burning 
                                                              //the commas   
   
   //sets the director name
   infile >> character;
   while(character != ','){
      director += character;
      infile.get(character);
   }
   
   //sets the movie title
   infile >> character;
   while(character != ','){
      title += character;
      infile.get(character);
   }
   infile >> actor >> name;
   actor += " ";
   actor += name;
   infile >> month >> releaseDate;
   
   return true;
}

// ---------------------------------------------------------------------------
//getActor
string Classic::getActor() const{
   return actor;
}
// ---------------------------------------------------------------------------
//displayMovie
void Classic::displayMovie(){    
   cout << type << " " << stock << " " << director << " " << title << " " << 
                        actor << " " << month << " " << releaseDate << endl;
}
// ---------------------------------------------------------------------------
//equals
bool Classic::equals(Transaction* right) const{
   return releaseDate == right->getYear() && actor == right->getActor();  
}