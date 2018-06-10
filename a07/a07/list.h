//
//  list.h
//  a07
//
//  Created by Justin Parry on 6/7/18.
//  Copyright © 2018 jEnoch. All rights reserved.
//

#ifndef list_h
#define list_h

namespace custom
{
   class list
   {
   public:
      /****************************************
       * CONSTRUCTORS
       ****************************************/
      list() : pHead(NULL), pTail(NULL), numElem(0) {}
      list(const list & rhs);
      ~list();
      list & operator = (const list & rhs) throw (const char *);
      
      /****************************************
       * STANDARD INTERFACES
       ****************************************/
      int size()
      {
         return numElem;
      }
      
      bool empty()
      {
         return (numElem == 0 && pHead == NULL);
      }
      
      void clear()
      {
         freeData(pHead);
         pTail = NULL;
         pHead = NULL;
         numElem = 0;
      }
      
      /****************************************
       * INTERFACES
       ****************************************/
      void push_back(const T & e) throw (const char *);
      void push_front(const T & e) throw (const char *);
      void pop_front() throw (const char *);
      void pop_back() throw (const char *);
      T & front() throw (const char *)
      {
         if (!empty())
         {
            return pHead -> data;
         }
         
         throw "ERROR: unable to access data from an empty list"
      }
      
      T & back() throw (const char *)
      {
         if (!empty)
      }
      T & find(const T & t);
      void erase(iterator & it);
      void insert(iterator & it; const T & t);
      iterator & begin();
      iterator & end();
      
   private:
      class Node;
      class iterator;
      Node * pHead;
      Node * pTail;
      int numElem;
   } // list
   
   template <class T>
   class list <T> :: Node
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
   
   /**************************************************
    * list ITERATOR
    * An iterator through vector
    *************************************************/
   template <class T>
   class list <T> :: iterator
   {
   public:
      // constructors, destructors, and assignment operator
      iterator()      : p(NULL)      {              }
      iterator(T * p) : p(p)         {              }
      iterator(const iterator & rhs) { *this = rhs; }
      iterator & operator = (const iterator & rhs)
      {
         this->p = rhs.p;
         return *this;
      }
      
      // equals, not equals operator
      bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
      bool operator == (const iterator & rhs) const { return rhs.p == this->p; }
      
      // dereference operator
      T & operator * ()       { return *p; }
      const T & operator * () const { return *p; }
      
      // prefix increment
      iterator & operator ++ ()
      {
         p = p -> pNext;;
         return *this;
      }
   
      // prefix decrement
      iterator & operator -- ()
      {
         p = p -> pPrev;
         return *this
      }
   private:
      T * p;
   }; // iterator
   
   /****************************************
    * NODE CONSTRUCTORS
    ****************************************/
   template <class T>
   typename list <T> :: Node <T> :: Node(const T & e)
   {
      data = e;
      pNext = NULL;
      pPrev = NULL;
   }
   
   /*****************************
    * NODE INSERT
    *
    *****************************/
   template <class T>
   list :: Node <T> * insert(Node <T> * pCurrent, const T & e, bool after = false) throw (const char *)
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
    * NODE FREE_DATA
    *
    *****************************/
   template <class T>
   list :: void freeData(Node <T> * & pHead)
   {
      while (pHead != NULL)
      {
         Node <T> * pDelete = pHead;
         pHead = pHead -> pNext;
         delete pDelete;
      }
   } // clear
   
   /*****************************
    * NODE COPY
    *
    *****************************/
   template <class T>
   typename list :: Node <T> list :: * copy(const Node <T> * pSource) throw (const char *)
   {
      
      
      try
      {
         Node <T> * pDestiny = new Node <T> (pSource -> data);
      }
      
      catch (std::bad_alloc)
      {
         throw "ERROR: unable to allocate a new buffer for list";
      }
      
//      Node <T> * pSrc = pSource;
      Node <T> * pDes = pDestiny;
      
      for (const Node <T> * p = pSource -> pNext; p; p = p -> pNext)
      {
         pDes = insert(pDes, p -> data, true);
      }
      
      return pDestiny;
   } // COPY
   
   /*****************************
    * NODE FIND
    *
    *****************************/
   template <class T>
   list <T> :: Node <T> * find(Node <T> * pHead, const T & e)
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
    * NODE REMOVE
    *
    *****************************/
   template <class T>
   list :: Node <T> * remove (const Node <T> * pRemove)
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
    * NODE INSERTION OPERATOR
    *
    *****************************/
   template <class T>
   list :: ostream & operator << (ostream & out, const Node <T> * const & rhs)
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

   /*****************************
    * LIST CONSTUCTORS
    *
    *****************************/
   template <class T>
   list <T> :: list(const list & rhs) throw (const char *)
   {
      if (rhs.size() == 0)
      {
         numElem = 0;
         pHead = pTail = NULL;
         return;
      }
      
      
      
   }
   
   /*****************************
    * LIST PUSH_BACK
    *
    *****************************/
   template <class T>
   void list <T> :: push_back(T & e) throw (const char *)
   {
      try
      {
         Node * pNewTail = new Node (e);
      }
      
      catch (std::bad_alloc)
      {
         throw "ERROR: unable to allocate a new node for a list";
      }
      
      if (empty())
      {
         pHead = pNewTail;
         return;
      }
      
      pNewTail -> pPrev = pTail;
      pTail -> pNext = pNewTail;
      pTail = pNewTail;
      
      numElem++;
   }
   
} //custom name


#endif /* list_h */
