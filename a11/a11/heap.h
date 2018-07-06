//
//  heap.h
//  a11
//
//  Created by Justin Parry on 7/3/18.
//  Copyright © 2018 jEnoch. All rights reserved.
//

#ifndef heap_h
#define heap_h

template <class T>
class heap
{

public:
   heap(T array[], int num);
   
   // percolate down takes an index and heapifies from that point down
   void percolateDown(int index);

   // turns array into a heap
   void heapify();
   
   // turns array from heap to sorted array
   void sort();
   
   // swaps the values at the given indices
   void swap(int i1, int i2);
   
   // get max to retun the max value in the heap
   T getMax()
   {
      int iMax = 0;
      for (int i = 0; i < array.size(); i++)
      {
         if (array[i] > array[iMax])
         {
            iMax = i;
         }
      }
      
      return array[iMax];
      
   }
   
   int getIMax()
   {
      int iMax;
      
      for (int i = 0; i < array.size(); i++)
      {
         if (array[i] > array[iMax])
         {
            iMax = i;
         }
      }
      
      return iMax;
      
   }
   
   // removes the max value in the heap
   void deleteMax()
   {
      int iMax = getIMax();
      
      for (int i = iMax; i < array.size(); i++)
      {
         array[i] = array[i + 1];
      }
   }
   
   
   
private:
   int num;
   T array[];
};

/****************************************************
 * HEAP :: CONSTRUCTOR
 ****************************************************/
template <class T>
heap <T> :: heap(T array[], int num)
{
   for (int i = 0; i < num; i++)
   {
      this->array[i] = array[i];
   }
   
   this->num = num;
}

/****************************************************
 * HEAP :: PERCOLATE DOWN
 * takes an index and heapifies from that point down
 ****************************************************/
template <class T>
void heap <T> :: percolateDown(int index)
{
   
   
   int iLeft = index * 2;
   int iRight = iLeft + 1;

   if (iRight <= num && array[iRight] > array[iLeft] && array[iRight] > array[index])
   {
      swap(index, iRight);
      percolateDown(iRight);
   }
   
   else if (iLeft <= num && array[iLeft] > array[index])
   {
      std::swap(array[index], array[iLeft]);
      percolateDown(iLeft);
   }
   
   return;
}

/****************************************************
 * HEAP :: HEAPIFY
 * turns array into a heap
 ****************************************************/
template <class T>
void heap <T> :: heapify()
{
   for (int index = (num / 2); index != 1; index++)
   {
      percolateDown(index);
   }
   
   return;
}

/****************************************************
 * HEAP :: SORT
 * turns array from heap to sorted array
 ****************************************************/
template <class T>
void heap <T> :: sort()
{
   int one = 1;
   if (num == 10)
   {
    std::cerr << "num == 10\n";
   }
   
   while (num > one)
   {
      swap (one, num);
      num--;
      percolateDown(one);
   }
   std::cerr << "after the while loop\n";
}


/****************************************************
 * HEAP :: SWAP
 * swaps the values at the given indices
 ****************************************************/
template <class T>
void heap <T> :: swap(int i1, int i2)
{
   T temp = array[i1];
   
   array[i1] = array[i2];
   
   array[i2] = temp;
   
   return;
}

#endif /* heap_h */
