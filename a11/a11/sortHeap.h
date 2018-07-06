/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

#include "heap.h"

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
   std::cerr << "num: " << num << std::endl;
   heap <T> h(array, num);
   
   h.sort();
   std::cerr << "after the sort functinos\n";
}


#endif // SORT_HEAP_H
