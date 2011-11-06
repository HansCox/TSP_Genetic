//SetInts.cpp

#include <cstdlib>
#include <iostream>
#include "LinkedListInts.cpp"

using namespace std;

class SetInts
{
      private:
        LinkedListInts *list;
        LinkInt* current;
      public:
        SetInts()
        { 
                 list = new LinkedListInts;
                 current = list->getFirst();
        }
        int find(int v)
        {
            return list->find(v);
        }    
        int insert(int v)
        {
            if(DEBUG)cout << "SetInts.insert(): Inserting solution ksldjflskdj..." << endl;
            int inserted = 0;
             if( v == 1 )
              {
                  if(DEBUG) cout << "SetInts.insert(): About to insert into list" << endl;
                    list->insertAtHead(1);
                    
                    inserted = 1;
              }
              else if( !list->find(v) )
             {
                 list->insertAtHead(v);
                 inserted = 1;
                 
             }
            
             return inserted;
        }
        int* summation(int array [][NUMBER_CITIES], int nCities)
        {
            return list->summation(array, nCities);
        }
        LinkInt* getFirst() { return list->getFirst(); }
        LinkInt* getCurrent() { return current; }
        LinkInt* getNext() { return current->getNext(); }
        void swapWithNext(LinkInt* aLink, LinkInt* previous)
        {
             list->swapWithNext(aLink);
        }
        void display() { list->display(); }
};
