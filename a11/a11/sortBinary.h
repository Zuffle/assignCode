/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   custom::BST <T> bst;
   int i;
   for (i = 0; i < num; i++)
   {
      bst.insert(array[i]);
   }
   i = 0;
   for (typename custom::BST <T> :: iterator it = bst.begin(); it != bst.end(); ++it)
   {
      array[i++] = *it;
   }
}


#endif // SORT_BINARY_H
