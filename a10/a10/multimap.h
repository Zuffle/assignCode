//
//  multimap.h
//  Week 10
//
//  Created by Taylor Williams on 6/25/18.
//  Copyright © 2018 Taylor Williams. All rights reserved.
//

#ifndef multimap_h
#define multimap_h

#include <iostream>

#include "bst.h"
#include "pair.h"

namespace custom {

template <class K, class V>
class multimap
{
public:
    /******** NESTED CLASSES ********/
    class iterator;
    
    /******** CONSTRUCTORS ********/
    multimap()
    {
        bst = new BST <pair <K, V> > ();
    }
    multimap(const multimap <K, V> & rhs) throw (const char *)
    {
        bst = new BST <pair <K, V> > ();
        *bst = *rhs.bst;
    }
    
     /******** OPERATORS ********/
    multimap & operator = (const multimap <K, V> & rhs) throw (const char *)
    {
        bst = new BST <pair <K, V> > ();
        *bst = *rhs.bst;
        return *this;
    }
    V & operator [] (const K & k)       throw (const char *);
    V   operator [] (const K & k) const throw (const char *);
    
    /******** ITERATOR METHODS ********/
    iterator begin();
    iterator end();
    
    /******** METHODS ********/
    int size()   { return bst->size();       }
    bool empty() { return bst->size() == 0;  }
    void clear() { bst->clear();             }
    
    iterator find(const K & k)
    {
        pair <K, V> p;
        p.first = k;
        multimap <K, V> :: iterator it = bst->find(p);
        return it;
    }
    
    void insert(const pair <K, V> & input) throw (const char *);
    void insert(const K & k, const V & v)  throw (const char *);
    
private:
    /******** MEMBERS ********/
    BST <pair <K, V> > * bst;
};

template <class K, class V>
V & multimap <K, V> :: operator [] (const K & k) throw (const char *)
{
    pair <K, V> p;
    p.first = k;
    multimap <K, V> :: iterator it(bst->find(p));
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
V multimap <K, V> :: operator [] (const K & k) const throw (const char *)
{
    pair <K, V> p;
    p.first = k;
    multimap <K, V> :: iterator it(bst->find(p));
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
void multimap <K, V> :: insert(const pair <K, V> & input) throw (const char *)
{
    /*multimap <K, V> :: iterator it(bst->find(input));
    if (it != bst->end())
        *it = input;
    else*/
    
    bst->insert(input);
}

template <class K, class V>
void multimap <K, V> :: insert(const K & k, const V & v) throw (const char *)
{
    
    /*multimap <K, V> :: iterator it(bst->find(p));
    if (it != bst->end())
        *it = p;
    else*/
    
    pair <K, V> p (k, v);
    bst->insert(p);
}
    
/********************************************************************
 * CLASS : ITERATOR : This will define an iterator to traverse a list
 ********************************************************************/
template <class K, class V>
class multimap <K, V> :: iterator
{
public:
    iterator() {}
    iterator(const iterator & rhs)
    {
        it = rhs.it;
    }
    iterator(const typename BST <pair <K, V> > :: iterator & rhs)
    {
        it = rhs;
    }
    iterator & operator = (const iterator & rhs)
    {
        it = rhs.it;
        return *this;
    }
    iterator & operator = (const typename BST <pair <K, V> > :: iterator & rhs)
    {
        it = rhs;
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
    pair<K, V> & operator * ()
    {
        return *it;
    }
    iterator operator ++ (int postfix)
    {
        iterator multimapIt(it);
        it++;
        return multimapIt;
    }
    iterator & operator ++ ()
    {
        ++it;
        return *this;
    }
    iterator operator -- (int postfix)
    {
        iterator multimapIt(it);
        it--;
        return multimapIt;
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
typename multimap <K, V> :: iterator multimap <K, V> :: begin()
{
    return bst->begin();
}
    
template <class K, class V>
typename multimap <K, V> :: iterator multimap <K, V> :: end()
{
    return bst->end();
}
  
    
    
}

#endif /* multimap_h */
