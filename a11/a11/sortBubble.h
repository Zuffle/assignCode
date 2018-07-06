/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Kirby, CS 235
 * Author:
 *    Lu Yuan Ting
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
   bool swapped;
   for (int iPivot = num - 1; iPivot >= 1; iPivot--)
   {
      swapped = false; 
      
      for (int iCheck = 0; iCheck <= iPivot - 1; iCheck++)
      {
         if (array[iCheck] > array[iCheck + 1])
         {
            T temp = array[iCheck];
            array[iCheck] = array[iCheck + 1];
            array[iCheck + 1] = temp;
            swapped = true;
         }
      }
      if(!swapped)
         return;
   }
}


#endif // SORT_BUBBLE_H
