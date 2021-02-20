#ifndef RETURN_H
#define RETURN_H
#include "borrow.h"

//---------------------------------------------------------------------------
// Return class inherits everything from the Borrow class, besides its type
//---------------------------------------------------------------------------

class Return: public Borrow{
  public:
   Return();
   ~Return();   
};
#endif