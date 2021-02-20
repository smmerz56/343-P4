#include "drama.h"

// ---------------------------------------------------------------------------
//displayMovie
Drama::Drama(){}

// ---------------------------------------------------------------------------
//displayMovie
Drama::~Drama(){}

// ---------------------------------------------------------------------------
//equals
//helps compare with a Transaction object
bool Drama::equals(Transaction* right) const{
   return director == right->getDirector() && title == right->getMovieTitle();  
}

