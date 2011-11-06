/* main.cpp
 * Finding a solution to the TSP
 * using a genetic algorithm.
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "SetInts.cpp"
#include "GLOBALS.H"



using namespace std;

void generateMap(int array[][NUMBER_CITIES])
{
     int rnum;
  
    for(int i=0; i<NUMBER_CITIES; i++)
    {
       for(int j=i; j<NUMBER_CITIES; j++)
       {
           if(i==j)
               array[i][j] = 0;
           else
           {
               rnum = rand() % 1000 + 1;
               array[i][j] = rnum;
               array[j][i] = rnum;
           }
       }               
    }
}

void displayCitiesArray(int array [][NUMBER_CITIES])
{
     for(int y=0;y<NUMBER_CITIES; y++)
     {
                     for(int z=0; z<NUMBER_CITIES; z++)
                     cout << array[y][z] << " ";
             cout << endl;        
     }
}


int readFile(int array [][NUMBER_CITIES])
{
    int success;
    int digit, distance;
    char ch;
    string line;
  ifstream myfile;
  myfile.open(FILENAME,ios::in);
  if (myfile.is_open())
  {
   if(DEBUG) cout << "Opened file " << FILENAME << endl;
   
      for(int start=0; start<NUMBER_CITIES; start++)
      {
        for(int dest=0; dest<NUMBER_CITIES; dest++)
        {
                getline(myfile,line);
                distance = 0;
                digit = 0;
          for(int i=0; i<line.length(); i++)
          {   
                  ch = line.at(i);
                 
                if( ch >= 48 && ch <= 57)
                {
                    digit = ch-48;
                    digit = digit * (int) pow(10.0,(int)line.length()-1);
                    distance += digit;
                 }            
          }   
          if(DEBUG) cout << "Putting distance in array of int[][]" << endl;
          array[start][dest] = distance;
         if(DEBUG) cout << "Distance from city " << start+1 << " to city " << dest+1 
               << " is " << array[start][dest] << "." << endl;
        }  
      } 
      displayCitiesArray(array);
    myfile.close();
    success = 1;
  }
  else 
  {
       
       success = 0;
  }
  return success; 
}

/*
 * generateSolutions()
 */
 void generateSolutions(SetInts* solutions [])
 {
      if(DEBUG) cout << "Inside function generateSolutions()" << endl;
   
   for(int k=0; k<NUMBER_SOLUTIONS; k++) 
   {
        
          if(DEBUG) cout << "Inserting starting city 1..." << endl;
           solutions[k]->insert(1);
           for(int m=1; m<NUMBER_CITIES; m++)
           {
                   int randomCity = rand() % NUMBER_CITIES + 1;
                   if ( randomCity!=1 )
                   {
                      if( solutions[k]->insert(randomCity) ) 
                           continue;
                      else m--;
                   }
                   else m--;
           }
           solutions[k]->insert(1);
   }
}

/*
 * computeWeights()
 */
void computeWeights(int* weights[], SetInts* solutions[], int array[][NUMBER_CITIES])
{
     /* 
            * Computing weights
            */
            for(int k; k<NUMBER_SOLUTIONS; k++)
            {
            weights[k] = solutions[k]->summation(array, NUMBER_CITIES);
            
            }
}

/*
 * displaySolsWts()
 */
void displaySolsWts(SetInts* solutions[], int* weights[])
{
     for(int k=0; k<NUMBER_SOLUTIONS; k++)
   {
            cout << "Solution " << k;
           solutions[k]->display();
            cout << ", Weight = " << *weights[k];
           cout << endl;
   }
}

/*
 * displayWts()
 */
 void displayWts(int* weights[])
 {
      for(int i=0; i<NUMBER_SOLUTIONS; i++)
      {
              cout << "Solution " <<i<< " weight = " << *weights[i] << endl;
      }
 }
  
/*
 * swapSolWts(), helper function to cullSolWts()
 */
void swapSols(int one, int two, SetInts *solutions[])
{
    SetInts tempSol;
    tempSol = *solutions[one];
    *solutions[one] = *solutions[two];    
    *solutions[two] = tempSol;
}

/*
 * swapWts(), helper function to cullSolWts()
 */
void swapWts(int one, int two, int* weights[])
{
     int tempWt;
     tempWt = *weights[one];
     *weights[one] = *weights[two];
     *weights[two] = tempWt;
}

/*
 * sortSolsByWt(), helper function to cullSolutions()?
 */
void sortSolsByWt(SetInts* solutions [], int* weights [])
{
    int out, in, min;
     
     for(out=0; out<NUMBER_SOLUTIONS-1; out++)
     {
          min = out;
          if(DEBUG) cout << "min = " << min << ", out = " << out << endl;
          for(in=out+1; in<NUMBER_SOLUTIONS; in++)
          {
                      if(DEBUG)  cout << "in = " << in << endl;
               if(*weights[in]<*weights[min] )
               {
               if(DEBUG)  
                  cout << *weights[in] <<"<" <<*weights[min] <<" new min\n";
               min = in;   
               }            
          }
          
         if(*weights[out]>*weights[min])
         {
          if(DEBUG) cout << *weights[out] <<">" <<*weights[min] << endl;
           if(DEBUG) cout << "Swapping solution "<<out<<"with solution "<<min<<endl;
             swapSols(out, min, solutions);  
                 swapWts(out, min, weights);
              if(DISPLAY_SOLUTIONS_EACH_ITERATION)
                  displaySolsWts(solutions, weights);   
         } 
     }
}


/*
 * Mutate a solution
 */
 void mutateSol(SetInts* solution)
 {
      int randomInt = rand() % 100;
      LinkInt* previous;
      /* Mutate solution */
      LinkInt *current = solution->getFirst();
      previous = current;
      while(current->getNext() != NULL)
      {
         if(100-randomInt <= MUTATE_PROBABILITY_IN_PERCENT
                          && current != solution->getFirst() 
         )
         {
                          solution->swapWithNext(current, previous);                       
         } 
         previous = current;
         current = current->getNext();
      } 
 }

/*
 * Computer average of solution weights
 */
 int computeAvgWt(int* weights [])
 {
      int sum = 0;
      for(int i=0; i<NUMBER_SOLUTIONS; i++)
              sum += *weights[i];
      return sum / NUMBER_SOLUTIONS;
 }

/*
 * displayOutput()
 */
 void displayOutput(SetInts* solutions[], int* weights[])
 {
      if(NUMBER_CITIES <= 10 && NUMBER_SOLUTIONS <=50) 
                       displaySolsWts(solutions, weights);
        else displayWts(weights);
 }



/*
 * main()
 */
int main(int argc, char *argv[])
{   
    int array [NUMBER_CITIES] [NUMBER_CITIES];
    SetInts *solutions [NUMBER_SOLUTIONS];
        for(int init=0; init<NUMBER_SOLUTIONS; init++)
            solutions[init] = new SetInts;
    int *weights [NUMBER_SOLUTIONS];
        for(int init2=0; init2<NUMBER_SOLUTIONS; init2++)
                weights[init2] = new int;
                
    generateMap(array);
    
    //displayCitiesArray(array);
  ///*
//   * Read data from file.
//   */  
//    if(readFile(array))
//      cout << "Read file into array." << endl;
//    else cout << "File reading failed -- unable to open file." << endl;
//  
  /*
   * Generate solutions
   */
   if(DISPLAY) cout << "Generating initial solution.." << endl;
   generateSolutions(solutions);
   /*
    * Compute weights of solutions.
    */
   if(DISPLAY) cout << "Computing weights..." << endl;
   computeWeights(weights, solutions, array);
   
   /*
    * Display each solutions with its weight.
    */
    if(DISPLAY) displayOutput(solutions, weights);
    
   /*
    * Sort solutions
    */
    if(DISPLAY) cout << "Sorting solutions by weight..." << endl;
    sortSolsByWt(solutions, weights);
   
   //Display solutions after weights have been computed 
        if(DISPLAY) displayOutput(solutions, weights);
        cout << "Average " << computeAvgWt(weights) 
              << "  Min " << *weights[0] << endl;
    
    /*
     * Cull and Mutate solution set
     */
     for(int j=0; j<MUTATE_N_TIMES; j++)
     {       
         for(int i=0; i<NUMBER_SOLUTIONS; i++)
         {
             if( (double) *weights[i] 
             > (double) *weights[0] 
             * (1.0 + CUTOFF_FRAC_OF_MIN_IN_PERCENT / 100.0)
             )
                 mutateSol(solutions[i]);
         }
       /*
        * Compute weights of solutions.
        */
        if(DISPLAY) cout << "Recomputing weights..." << endl;
       computeWeights(weights, solutions, array);
       if(DISPLAY) cout << "Sorting list..." << endl;
       sortSolsByWt(solutions, weights);
       
       //Display solutions after weights have been computed 
        if(DISPLAY) displayOutput(solutions, weights);
         cout << "Average " << computeAvgWt(weights) 
              << "  Min " << *weights[0] << endl;
     }
       
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

