#include "movie.h"

// --------------------------------------------------------------------------- 
//constructor
Movie::Movie(){
   type = ' ';
   stock = 0;
   director = "";
   title = "";
   releaseDate = 0;
}  

// ---------------------------------------------------------------------------
//destructor
Movie::~Movie(){}    
 
// ---------------------------------------------------------------------------
//setData
//Precondition: needs the genre already read in from Manager
// sets the data from a file
bool Movie::setData(char genre, ifstream& infile){     
   type = genre;
   char character;
   string name;
   infile >> character >> stock >> character;//the characters are burning
                                                               // the commas   
   
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
   infile >> releaseDate;
  
   return true;
}

// ---------------------------------------------------------------------------
//displayMovie
void Movie::displayMovie(){    
   cout << type << " " << stock << " " << director << " " << title << " " 
                                                      << releaseDate << endl; 
}
// ---------------------------------------------------------------------------
//operator<
bool Movie::operator<(const Movie& right) const{
   return title < right.title; 
}
// ---------------------------------------------------------------------------
//operator==
bool Movie::operator==(const Movie& right) const{
   return title == right.title;
}
// ---------------------------------------------------------------------------
//equals
bool Movie::equals(Transaction* right) const{
   return title == right->getMovieTitle();  
}
// ---------------------------------------------------------------------------
//getActor
string Movie::getActor() const{ 
   return "none";
}
// ---------------------------------------------------------------------------
//getDirector
string Movie::getDirector() const{
   return director;
}
// ---------------------------------------------------------------------------
//getTitle
string Movie::getTitle() const{
   return title;
}
// ---------------------------------------------------------------------------
//getReleaseDate
int Movie::getReleaseDate() const{
   return releaseDate;
}