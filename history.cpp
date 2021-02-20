#include "history.h"

// ---------------------------------------------------------------------------
// constructor
History::History(){}

// ---------------------------------------------------------------------------
// two parameter constructor for use in Manager
History::History(char t, int c){
   type = t;
   customerNumber = c;
}

// ---------------------------------------------------------------------------
// destructor
History::~History(){} 