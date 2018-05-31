//
//  Node.h
//  a06
//
//  Created by Justin Parry on 5/28/18.
//  Copyright © 2018 jEnoch. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <iostream>
using std::ostream;

template <class T>
class Node
{
public:
   /****************************************
    * Data and pointers
    ****************************************/
   T data;
   Node * pNext;
   Node * pPrev;
   
   /****************************************
    * CONSTRUCTORS
    ****************************************/
   Node() : data(T()), pNext(NULL), pPrev(NULL) {}
   Node(const T & e);
   
}; // Node

/****************************************
 * CONSTRUCTORS
 ****************************************/
template <class T>
Node <T> :: Node(const T & e)
{
   data = e;
   pNext = NULL;
   pPrev = NULL;
}

/****************************************
 * INTERFACES
 ****************************************/

/*****************************
 * INSERT
 *
 *****************************/
template <class T>
Node <T> * insert(Node <T> * pCurrent, const T & e, bool after = false) throw (const char *)
{
   Node <T> * pNew = new Node <T> (e);
   
   if (pCurrent != NULL && after == false)
   {
      pNew -> pNext = pCurrent;
      pNew -> pPrev = pCurrent -> pPrev;
      pCurrent -> pPrev = pNew;
      
      if (pNew -> pPrev)
      {
         pNew -> pPrev -> pNext = pNew;
      }
   }
   
   if (pCurrent != NULL && after == true)
   {
      pNew -> pNext = pCurrent -> pNext;
      pNew -> pPrev = pCurrent;
      pCurrent -> pNext = pNew;
      
      if (pNew -> pNext)
      {
         pNew -> pNext -> pPrev = pNew;
      }
   }
   
   return pNew;
} // insert

/*****************************
 * FREE_DATA
 *
 *****************************/
template <class T>
void freeData(Node <T> * & pHead)
{
   while (pHead != NULL)
   {
      Node <T> * pDelete = pHead;
      pHead = pHead -> pNext;
      delete pDelete;
   }
} // clear

/*****************************
 * COPY
 *
 *****************************/
template <class T>
Node <T> * copy(const Node <T> * pSource) throw (const char *)
{
   Node <T> * pDestiny = new Node <T> (pSource -> data);
   const Node <T> * pSrc = pSource;
   Node <T> * pDes = pDestiny;
   
   for (const Node <T> * p = pSrc; p; p = p -> pNext)
   {
      pDes = insert(pDes, p -> data, true);
   }
   
   return pDestiny;
} // COPY

/*****************************
 * FIND
 *
 *****************************/
template <class T>
Node <T> * find(Node <T> * pHead, const T & e)
{
   for (Node <T> * p = pHead; p; p = p -> pNext)
   {
      if (p -> data == e)
      {
         return p;
      }
   }
   return NULL;
}

/*****************************
 * REMOVE
 *
 *****************************/
template <class T>
Node <T> * remove (const Node <T> * pRemove)
{
   if (NULL == pRemove)
      return NULL;
   
   if (pRemove -> pPrev)
      pRemove -> pPrev -> pNext = pRemove -> pNext;
   if (pRemove -> pPrev)
      pRemove -> pNext -> pPrev = pRemove -> pPrev;
   
   Node <T> * pReturn = NULL;
   
   if (pRemove -> pPrev)
      pReturn = pRemove -> pPrev;
   else
      pReturn = pRemove -> pNext;
   
   delete pRemove;
   return pReturn;
} // ReMOVE

/*****************************
 * INSERTION OPERATOR
 *
 *****************************/
template <class T>
ostream & operator << (ostream & out, const Node <T> * const & rhs)
{
   bool first = true;
   for (const Node <T> * p = rhs; p; p = p -> pNext)
   {
      if (first)
      {
         out << p -> data;
         first = false;
      }
      else
         out << ", " << p -> data;
   }
   
   return out;
}


#endif /* Node_h */
