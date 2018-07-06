/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{  
   for (int i = 0; i < num - 1; i++)
   {
      int iMin = i;
      for(int j = i + 1; j < num; j++)
      {
         if(array[j] < array[iMin])
            iMin = j;
      }
      T temp = array[i];
      array[i] = array[iMin];
      array[iMin] = temp;
   }
}


#endif // SORT_SELECTION_H
