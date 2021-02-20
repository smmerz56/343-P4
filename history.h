#ifndef HISTORY_H
#define HISTORY_H
#include "transaction.h"

// ---------------------------------------------------------------------------
// History Class inherits most of the Transaction class
// ---------------------------------------------------------------------------

class History: public Transaction{
public:
   History();
   History(char, int);// for use in Manager
   ~History();
   
};
#endif