/*
  Name: README.txt
  Copyright: none
  Author: Hans Cox
  Date: 06/11/11 16:52
  Description: Description of TSP_Genetic program, which, as of today, has a bug.
*/



Solving the Traveling Sales[Person] Problem for N cities using a "genetic" (sort of) algorithm.

The program makes a map (an array of distances between cites) for number of cities determined by NUMBER_CITIES defined in GLOBALS.H.

A set of random solutions, number determined by NUMBER_SOLUTIONS in GLOBALS.H, is generated. The solutions are sorted by weight, least first. Then all the solutions that have weights a certain amount above the minimum for that solution set are randomly mutated. The number of mutation iterations is determined by MUTATE_N_TIMES in GLOBALS.H.

Source files are GLOBALS.H, LinkedListInts.cpp, LinkInt.cpp, main.cpp and SetInts.cpp. Text file (optional) is newcities.txt.

Bug: If DISPLAY, defined in GLOBALS.H, is not set, the solutions do not get realistic weights (e.g., for a set of 20 cities, with random distances of up to 999, a minimum solution will be given as having a weight of 4. This is impossible!)
This bug occurs on only the first iteration (or first few), performed outside the mutation loop. How can DISPLAY have this effect? It works fine with DISPLAY == 1!
