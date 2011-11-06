//LinkInt.cpp

#include <cstdlib>
#include <iostream>
#include "GLOBALS.H"
using namespace std;

class LinkInt
{
      private:
              int value;
              LinkInt *next;
      public:
             LinkInt()
             {  
                      value = 0;
                next = NULL;
                 }
             LinkInt(int v)
             { 
               if(DEBUG) 
                 cout << "Constructing new initialized LinkInt object" << endl;
               value = v; 
               next = NULL;
             }
             LinkInt(LinkInt& toCopy)
             {
                        value = toCopy.value;
                        next = toCopy.next;      
             }
             int getValue()
             { return value; }
             void setValue(int v)
             { value = v; }
             LinkInt* getNext()
             { return next; }
             void setNext(LinkInt* n)
             { next = n; }
             void display()
             { cout << value; }
};
