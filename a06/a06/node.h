//
//  node.h
//  a06
//
//  Created by Justin Parry on 5/28/18.
//  Copyright © 2018 jEnoch. All rights reserved.
//

#ifndef node_h
#define node_h

template <class T>
class node
{
public:
   /****************************************
    * Data and pointers
    ****************************************/
   T data;
   node * pNext;
   node * pPrev;
   
   /****************************************
    * CONSTRUCTORS
    ****************************************/
   node() : data(NULL), pNext(NULL), pPrev(NULL) {}
   node(const T & e);
   
   /****************************************
    * INTERFACES
    ****************************************/
   node <T> * insert(node <T> * pCurrent, const T & e, bool after = false) throw (const char *);
   node <T> * find(node <T> * pHead, const T & e);
   void freeData(node <T> * & pHead);
   node <T> * copy(const node <T> * pSource) throw (const char *);
   node <T> * remove (const node <T> * pRemove);
   
}; // node
/****************************************
 * CONSTRUCTORS
 ****************************************/
template <class T>
node <T> :: node(const T & e)
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
node <T> * insert(node <T> * pCurrent, const T & e, bool after = false) throw (const char *)
{
   node <T> * pNew = new node <T> (e);
   
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
void freeData(node <T> * & pHead)
{
   while (pHead != NULL)
   {
      node <T> * pDelete = pHead;
      pHead = pHead -> pNext;
      delete pDelete;
   }
} // clear

/*****************************
 * COPY
 *
 *****************************/
template <class T>
node <T> * copy(const node <T> * pSource) throw (const char *)
{
   node <T> * pDestiny = new node <T> (pSource -> data);
   const node <T> * pSrc = pSource;
   node <T> * pDes = pDestiny;
   
   for (const node <T> * p = pSrc; p; p = p -> pNext)
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
node <T> * find(node <T> * pHead, const T & e)
{
   for (node <T> * p = pHead; p; p = p -> pNext)
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
node <T> * remove (const node <T> * pRemove)
{
   if (NULL == pRemove)
      return NULL;
   
   if (pRemove -> pPrev)
      pRemove -> pPrev -> pNext = pRemove -> pNext;
   if (pRemove -> pPrev)
      pRemove -> pNext -> pPrev = pRemove -> pPrev;
   
   node <T> * pReturn = NULL;
   
   if (pRemove -> pPrev)
      pReturn = pRemove -> pPrev;
   else
      pReturn = pRemove -> pNext;
   
   delete pRemove;
   return pReturn;
} // ReMOVE

   


#endif /* node_h */
