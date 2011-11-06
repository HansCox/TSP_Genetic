//LinkedListInt

#include <cstdlib>
#include <iostream>
#include "LinkInt.cpp"
#include "GLOBALS.H"

using namespace std;

class LinkedListInts
{
      private:
       LinkInt *first;
      public:
       LinkedListInts()
       { 
          if(DEBUG)cout << "Initializing new LinkedListInts" << endl;
           first = NULL; 
       }          
       
       LinkInt* getFirst() { return first; }
          
       void insertAtHead(int v)
       {
       if(DEBUG)cout << "LinkedListInts.insertAtHead(): Inserting" << endl;
              if(first == NULL)
              {
              if(DEBUG)cout << "LinkedListInts.insertAtHead():first == NULL -- Creating first link" << endl;
                  first = new LinkInt(v);               
              }    
              else
              {
                  if(DEBUG)cout << "LinkedListInts.insertAtHead(): List not empty: inserting next link" << endl;
                  LinkInt *temp = new LinkInt(v);
                  temp->setNext(first);
                  first = temp;              
              }   
       }      
       int find(int v)
       {
                int found = 0;
                LinkInt *current = first;
                while(current!=NULL)
                {
                    if(current->getValue() == v)
                       found = 1;
                    current = current->getNext();
                }
                return found;
       }
       int getDistance(LinkInt* current, LinkInt* previous,
            int array[][NUMBER_CITIES], int nCities)
       {
           
           int distance = 0;
           int start, dest;
           start = previous->getValue();
           dest = current->getValue();
           distance = array[start-1][dest-1];
          
           return distance;
       }
       int* summation(int array[][NUMBER_CITIES], int nCities)
       {
           int *sum = new int;
           *sum = 0;
           LinkInt *current, *previous;
           previous = first;
           current = first->getNext();
           
           while(current->getNext()!=NULL)
           {
               
               *sum += getDistance(current, previous, array, nCities);
              
               previous = current;
               current = current->getNext();                          
           }
           return sum;
       }         
       int swapWithNext(LinkInt* aLink)
       {
                   int temp;
                   temp = ( aLink->getNext() )->getValue();
                   ( aLink->getNext() )->setValue( aLink->getValue() );
                   aLink->setValue(temp);
       }          
       void display()
       {
            LinkInt *current = first;
            cout << "[ ";
            if(current == NULL)
            cout << " ]";
            else
            {
                while(current != NULL)
                {            
                   current->display();
                   if(current->getNext() == NULL)
                     cout << " ]";
                   else  
                     cout << ", ";
                   current = current->getNext();
                  }                                     
            }
       }
};
