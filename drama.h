#ifndef DRAMA_H
#define DRAMA_H
#include "movie.h"
#include "transaction.h"

// ---------------------------------------------------------------------------
// Drama class inherits from the Movie class
// ---------------------------------------------------------------------------

class Drama: public Movie {
public:
   Drama();
   ~Drama();
   
   bool equals(Transaction*) const;// compare with a Transaction object
};
#endif