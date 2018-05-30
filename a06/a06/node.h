//
//  node.h
//  a06
//
//  Created by Justin Parry on 5/28/18.
//  Copyright © 2018 jEnoch. All rights reserved.
//

#ifndef node_h
#define node_h

namespace custom
{
   template <class T>
   class node
   {
   public:
      /****************************************
       * Data and pointers
       ****************************************/
      T * data;
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
      node <T> * insert(node <T> * pNode, const T & e, bool after = false) throw (const char *);
      node <T> * find(node <T> * pHead, const T & e);
      void clear(node <T> * & pHead);
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
   template <class T>
   node <T> :: node <T> * insert(node <T> * pNode, const T & e, bool after = false) throw (const char *)
   {
      
   }
   
}// custom

#endif /* node_h */
