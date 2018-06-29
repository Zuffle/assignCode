//
//  map.h
//  Week 10
//
//  Created by Taylor Williams on 6/25/18.
//  Copyright © 2018 Taylor Williams. All rights reserved.
//

#ifndef map_h
#define map_h

#include <iostream>

#include "bst.h"
#include "pair.h"

namespace custom {
   
   template <class K, class V>
   class map
   {
   public:
      /******** NESTED CLASSES ********/
      class iterator;
      
      /******** CONSTRUCTORS ********/
      map()
      {
         bst = new BST <pair <K, V> > ();
      }
      
      map(const map <K, V> & rhs) throw (const char *)
      {
         bst = new BST <pair <K, V> > ();
         *bst = *rhs.bst;
      }
      
      map & operator = (const map <K, V> & rhs) throw (const char *)
      {
         bst = new BST <pair <K, V> > ();
         *bst = *rhs.bst;
         return *this;
      }
      
      V & operator [] (const K & k)       throw (const char *);
      V   operator [] (const K & k) const throw (const char *);
      
      iterator begin();
      iterator end();
      
      /******** METHODS ********/
      int size()   { return bst->size();       }
      bool empty() { return bst->size() == 0;  }
      void clear() { bst->clear(); bst = NULL; }
      
      iterator find(const K & k)
      {
         pair <K, V> p;
         p.first = k;
         map <K, V> :: iterator it = bst->find(p);
         return it;
      }
      
   private:
      BST <pair <K, V> > * bst;
   };
   
   
   template <class K, class V>
   V & map <K, V> :: operator [] (const K & k) throw (const char *)
   
   {
      pair <K, V> p;
      p.first = k;
      map <K, V> :: iterator it = bst->find(p);
      if (it != bst->end())
      {
         return (*it).second;
      }
      
      else
      {
         bst->insert(p);
         return (*bst->find(p)).second;
      }
   }
   
   template <class K, class V>
   V map <K, V> :: operator [] (const K & k) const throw (const char *)
   {
      pair <K, V> p;
      p.first = k;
      map <K, V> :: iterator it = bst->find(p);
      if (it != bst->end())
      {
         return (*it).second;
      }
      else
      {
         bst->insert(p);
         return (*bst->find(p)).second;
      }
   }
   
   /********************************************************************
    * CLASS : ITERATOR : This will define an iterator to traverse a list
    ********************************************************************/
   template <class K, class V>
   class map <K, V> :: iterator
   {
   public:
      iterator();
      iterator(const iterator & rhs);
      iterator(const typename BST <pair <K, V> > :: iterator & rhs)
      {
         it = rhs;
      }
      
      iterator & operator = (const iterator & rhs)
      {
         it = rhs.it;
         return *this;
      }
      
      bool operator == (const iterator & rhs)
      {
         return it == rhs.it;
      }
      
      bool operator != (const iterator & rhs)
      {
         return it != rhs.it;
      }
      
      pair <K, V> & operator * () // note: fixed this to pair
      {
         return *it;
      }
      
      iterator operator ++ (int postfix)
      {
         iterator mapIt(it);
         it++;
         return mapIt;
      }
      
      iterator & operator ++ ()
      {
         ++it;
      }
      
      iterator operator -- (int postfix)
      {
         iterator mapIt(it);
         it--;
         return mapIt;
      }
      
      iterator & operator -- ()
      {
         --it;
         return *this;
      }
      
   private:
      typename BST <pair <K, V> > :: iterator it;
   };
   
   template <class K, class V>
   typename map <K, V> :: iterator map <K, V> :: begin()
   {
      return bst->begin();
   }
   
   template <class K, class V>
   typename map <K, V> :: iterator map <K, V> :: end()
   {
      return bst->end();
   }
   
   
   
}

#endif /* map_h */
