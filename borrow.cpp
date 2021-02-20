#include "borrow.h"
//---------------------------------------------------------------------------
// constructor
Borrow::Borrow(){
   type = 'B'; 
   mediaType = 'D';
}

//---------------------------------------------------------------------------
// destructor
Borrow::~Borrow(){} 

//---------------------------------------------------------------------------
// setData
// sets the data from a file
void Borrow::setData(int c, ifstream& infile){ 
   char character;
   string last;
   string line;
   customerNumber = c;
   infile >> movieGenre;
   
   if(movieGenre == 'F'){// if movie is a comedy
      infile >> character;
      while(character != ','){
         movieTitle += character;
         infile.get(character);
      }
      infile >> year;
      
   }
   else if(movieGenre == 'D'){// if movie is a drama
      infile >> character;
      while(character != ','){
         director += character;
         infile.get(character);
      }
      infile >> character;
      while(character != ','){
         movieTitle += character;
         infile.get(character);
      }
      
   }
   else if(movieGenre == 'C'){// if movie is a classic
      infile >> month >> year >> actor >> last;
      actor += " "; 
      actor += last;      
   }
   else{// if movie is invalid
      getline(infile, line);
      cout << "Invalid video code for transaction: " << type << " " 
               << customerNumber << " " << mediaType << " " << movieGenre 
                                                         << line << endl;
   }
    
}

//---------------------------------------------------------------------------
//display
// displays the borrow object
void Borrow::display(){
   if(movieGenre == 'F'){
      cout << type << " " << customerNumber << " " << mediaType << " " << 
                  movieGenre << " " << movieTitle << " " << year << endl;
   }
   else if(movieGenre == 'D'){
      cout << type << " " << customerNumber << " " << mediaType << " " << 
               movieGenre << " " << director << " " << movieTitle << endl;
   }
   else if(movieGenre == 'C'){
      cout << type << " " << customerNumber << " " << mediaType << " " << 
         movieGenre << " " << month << " " << year << " " << actor << endl;
   }
}
//---------------------------------------------------------------------------
//getMovieTitle
string Borrow::getMovieTitle() const{
   return movieTitle;
}
//---------------------------------------------------------------------------
//getYear
int Borrow::getYear() const{
   return year;
}
//---------------------------------------------------------------------------
//getDirector
string Borrow::getDirector() const{
   return director;
}
//---------------------------------------------------------------------------
//getActor
string Borrow::getActor() const{
   return actor;
}
//---------------------------------------------------------------------------
//getMovieGenre
char Borrow::getMovieGenre() const{  
   return movieGenre;
}