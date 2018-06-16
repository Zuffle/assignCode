//
//  list.h
//  Week 7
//
//  Created by Taylor Williams on 6/2/18.
//  Copyright © 2018 Taylor Williams. All rights reserved.
//

#ifndef list_h
#define list_h

#include <iostream>
using namespace std;

namespace custom
{

template <class T>
class Node;

template <class T>
class iterator;

template <class T>
class reverse_iterator;
    
/**********************************************
 *              CLASS: LIST
 * This will define a list of items
 *********************************************/
template <class T>
class list {
public:
    /************** NESTED CLASSES **************/
    class iterator;
    class reverse_iterator;
    class const_iterator;
    class const_reverse_iterator;
    class Node;
    
    /************** CONSTRUCTORS **************/
    list() : numElements(0), pHead(NULL), pTail(NULL) {}
    list(list & rhs) throw (const char *);
    ~list() { freeData(pHead); }
    
    /**************** METHODS ****************/
    int size()   { return numElements;   }  // Check to see how many items are in the list
    bool empty() { return pHead == NULL; }  // Check to see if the list is empty
    void clear()                            // This will set the list to default values
    {
        freeData(pHead);
        pHead = NULL;
        pTail = NULL;
        numElements = 0;
    }
    
    // Return the first and last item //
    T & front() throw (const char *)
    {
        if (!empty())
            return pHead->data;
        throw "ERROR: unable to access data from an empty list";
    }
    T & back() throw (const char *)
    {
        if (!empty())
            return pTail->data;
        throw "ERROR: unable to access data from an empty list";
    }

    // Iterator Functions //
    iterator begin()
    {
        return iterator(pHead);
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator (pTail);
    }
    iterator end()
    {
        if (!empty())
            return iterator (pTail->pNext);
        else
            return NULL;
    }
    reverse_iterator rend()
    {
        if (!empty())
            return reverse_iterator (pHead->pPrev);
        else
            return NULL;
    }
    // Constant Iterator Functions //
    const_iterator begin() const
    {
        return iterator(pHead);
    }
    const_reverse_iterator rbegin() const
    {
        return reverse_iterator (pTail);
    }
    const_iterator end() const
    {
        if (!empty())
            return iterator (pTail->pNext);
        else
            return NULL;
    }
    const_reverse_iterator rend() const
    {
        if (!empty())
            return reverse_iterator (pHead->pPrev);
        else
            return NULL;
    }
    
    
    void push_back(const T & t) throw (const char *);
    void push_front(const T & t) throw (const char *);
    iterator insert (iterator it, const T & t) throw (const char *);
    void erase(iterator & it) throw (const char *);
    iterator find(const T & t);
    
    /************ Additional Functions ************/

    void freeData(Node * & pHead);
    list & operator = (list & rhs) throw (const char *);
    
private:
    /**********   VARIABLES   **********/
    int numElements;
    Node * pHead;
    Node * pTail;
};

/***********************************************************
 *                     CLASS: NODE
 * Defines a simple Node class
 **********************************************************/
template <class T>
class list <T> :: Node
{
public:
    /*** VARIABLES ***/
    T data;                         // The data in the Node
    Node * pNext;               // Pointer to the next item in the list
    Node * pPrev;               // Pointer to the previoud item in the list
    
    /*** CONSTRUCTORS ***/
    Node () : data(T()), pNext(NULL), pPrev(NULL) {}
    Node (const T & t) : data(t), pNext(NULL), pPrev(NULL) {}
};


/**********************************************
 *              CLASS: ITERATOR
 * This will define an iterator to traverse a
 *  list
 *********************************************/
template <class T>
class list <T> :: iterator
{
    friend class list <T>;
    
    //friend iterator list <T> :: insert(iterator & it, const T & data) throw (const char *);
    //friend iterator list <T> :: erase(iterator & it, const T & data) throw (const char *);
    
public:
    iterator() : p(NULL) {}
    iterator(list <T> :: Node * it) : p(it) {}
    iterator(list <T> :: iterator const & it) { this->p = it.p; }
    
    bool operator == (const list <T> :: iterator & rhs) const
    {
        return rhs.p == this->p;
    }
    
    // not equals operator
    bool operator != (const list <T> :: iterator & rhs) const
    {
        return rhs.p != this->p;
    }
    
    // prefix increment
    list <T> :: iterator & operator ++ ()
    {
        p = p->pNext;
        return *this;
    }
    
    
    // postfix increment
    list <T> :: iterator operator++(int postfix)
    {
        iterator tmp(*this);
        p = p->pNext;
        return tmp;
    }
    
    list <T> :: iterator & operator -- ()
    {
        p = p->pPrev;
        return *this;
    }
    
    // postfix increment
    list <T> :: iterator operator--(int postfix)
    {
        iterator tmp(*this);
        p = p->pPrev;
        return tmp;
    }
    
    // dereference operator
    T & operator * ()
    {
        return p->data;
    }
    
private:
    typename list <T> :: Node * p;
};

/**********************************************
 *              CLASS: REVERSE_ITERATOR
 * This will define an iterator to traverse a
 *  list
 *********************************************/
template <class T>
class list <T> :: reverse_iterator
{
    friend class list <T>;
    //friend reverse_iterator list <T> :: insert(reverse_iterator & it, const T & data) throw (const char *);
    //friend reverse_iterator list <T> :: erase(reverse_iterator & it, const T & data) throw (const char *);
    
public:
    reverse_iterator() : p(NULL) {}
    reverse_iterator(list <T> :: Node * it) : p(it) {}
    reverse_iterator(list <T> :: reverse_iterator const & it) { this->p = it.p; }
    
    bool operator == (const list <T> :: reverse_iterator & rhs) const
    {
        return rhs.p == this->p;
    }
    
    // not equals operator
    bool operator != (const list <T> :: reverse_iterator & rhs) const
    {
        return rhs.p != this->p;
    }
    
    // prefix increment
    list <T> :: reverse_iterator & operator ++ ()
    {
        p = p->pPrev;
        return *this;
    }
    
    
    // postfix increment
    list <T> :: reverse_iterator operator++(int postfix)
    {
        reverse_iterator tmp(*this);
        p = p->pPrev;
        return tmp;
    }
    
    list <T> :: reverse_iterator & operator -- ()
    {
        p = p->pNext;
        return *this;
    }
    
    // postfix increment
    list <T> :: reverse_iterator operator--(int postfix)
    {
        reverse_iterator tmp(*this);
        p = p->pNext;
        return tmp;
    }
    
    // dereference operator
    T & operator * ()
    {
        return p->data;
    }
    
private:
    typename list <T> :: Node * p;
};

/**********************************************
 *              CLASS: ITERATOR
 * This will define an iterator to traverse a
 *  list
 *********************************************/
template <class T>
class list <T> :: const_iterator
{
    friend class list <T>;
    
    //friend iterator list <T> :: insert(iterator & it, const T & data) throw (const char *);
    //friend iterator list <T> :: erase(iterator & it, const T & data) throw (const char *);
    
public:
    const_iterator() : p(NULL) {}
    const_iterator(list <T> :: Node * it) : p(it) {}
    const_iterator(list <T> :: const_iterator const & it) { this->p = it.p; }
    
    bool operator == (const list <T> :: const_iterator & rhs) const
    {
        return rhs.p == this->p;
    }
    
    // not equals operator
    bool operator != (const list <T> :: const_iterator & rhs) const
    {
        return rhs.p != this->p;
    }
    
    // prefix increment
    list <T> :: const_iterator & operator ++ ()
    {
        p = p->pNext;
        return *this;
    }
    
    
    // postfix increment
    list <T> :: const_iterator operator++(int postfix)
    {
        const_iterator tmp(*this);
        p = p->pNext;
        return tmp;
    }
    
    list <T> :: const_iterator & operator -- ()
    {
        p = p->pPrev;
        return *this;
    }
    
    // postfix increment
    list <T> :: const_iterator operator--(int postfix)
    {
        const_iterator tmp(*this);
        p = p->pPrev;
        return tmp;
    }
    
    // dereference operator
    T & operator * ()
    {
        return p->data;
    }
    
private:
    typename list <T> :: Node * p;
};

/**********************************************
 *              CLASS: REVERSE_ITERATOR
 * This will define an iterator to traverse a
 *  list
 *********************************************/
template <class T>
class list <T> :: const_reverse_iterator
{
    friend class list <T>;
    //friend reverse_iterator list <T> :: insert(reverse_iterator & it, const T & data) throw (const char *);
    //friend reverse_iterator list <T> :: erase(reverse_iterator & it, const T & data) throw (const char *);
    
public:
    const_reverse_iterator() : p(NULL) {}
    const_reverse_iterator(list <T> :: Node * it) : p(it) {}
    const_reverse_iterator(list <T> :: const_reverse_iterator const & it) { this->p = it.p; }
    
    bool operator == (const list <T> :: const_reverse_iterator & rhs) const
    {
        return rhs.p == this->p;
    }
    
    // not equals operator
    bool operator != (const list <T> :: const_reverse_iterator & rhs) const
    {
        return rhs.p != this->p;
    }
    
    // prefix increment
    list <T> :: const_reverse_iterator & operator ++ ()
    {
        p = p->pPrev;
        return *this;
    }
    
    
    // postfix increment
    list <T> :: const_reverse_iterator operator++(int postfix)
    {
        const_reverse_iterator tmp(*this);
        p = p->pPrev;
        return tmp;
    }
    
    list <T> :: const_reverse_iterator & operator -- ()
    {
        p = p->pNext;
        return *this;
    }
    
    // postfix increment
    list <T> :: const_reverse_iterator operator--(int postfix)
    {
        const_reverse_iterator tmp(*this);
        p = p->pNext;
        return tmp;
    }
    
    // dereference operator
    T & operator * ()
    {
        return p->data;
    }
    
private:
    typename list <T> :: Node * p;
};

/**********************************************
 *             COPY CONSTRUCTOR
 *  Creates a copy of the list
 *********************************************/
template <class T>
list <T> :: list(list <T> & rhs) throw (const char *)
{
    numElements = 0;
    pHead = NULL;
    pTail = NULL;
    
    try
    {
        for (iterator it = rhs.begin(); it != rhs.end(); it++)
        {
            this->push_back(*it);
        }
    }
    catch(std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

/**********************************************
 *              OPERATOR: =
 *  Copies a list using the = operator
 *********************************************/
template <class T>
list <T> & list <T> :: operator = (list <T> & rhs) throw (const char *)
{
    numElements = 0;
    pHead = NULL;
    pTail = NULL;
    
    try
    {
        for (iterator it = rhs.begin(); it != rhs.end(); it++)
        {
            this->push_back(*it);
        }
    }
    catch(std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
    
    return *this;
}

/**********************************************
 *              PUSH_BACK()
 *  Places an item onto the back of the list
 *********************************************/
template <class T>
void list <T> :: push_back(const T & t) throw (const char *)
{
    try
    {
        Node * pNew = new Node (t);
        
        if (pTail != NULL)
        {
           pNew->pPrev = pTail;
           pTail->pNext = pNew;
           pNew->pNext = NULL;
           pTail = pNew;
        }
        else
        {
            pHead = pNew;
            pTail = pNew;
        }
        numElements++;
    }
    catch(std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

/**********************************************
 *              PUSH_FRONT()
 *  Places an item onto the front of the list
 *********************************************/
template <class T>
void list <T> :: push_front(const T & t) throw (const char *)
{
    try
    {
        Node * temp = new Node (t);
        
        if (pHead != NULL)
        {
           std::cerr << "pHead != NULL\n";
            temp->pNext = pHead;
            pHead->pPrev = temp;
            temp->pPrev = NULL;
            
            pHead = temp;
        }
        else if (pHead == NULL)
        {
            pHead = temp;
            pTail = temp;
        }
        numElements++;
    }
    catch(std::bad_alloc)
    {
        throw "ERROR: unable to allocate a new node for a list";
    }
}

/*************************************************
 *                INSERT()
 *  Inserts an item before where the passed in
 *      Iterator is pointing to
 ************************************************/
template <class T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it, const T & t) throw (const char *)
{
   try
   {
      Node * pNew = new Node(t);
       
      if (it.p != NULL)
      {
         pNew->pNext = it.p;
         pNew->pPrev = it.p->pPrev;
         it.p->pPrev = pNew;
         
         if (pNew->pPrev)
            pNew->pPrev->pNext = pNew;
         
         if (!pNew->pPrev)
            pHead = pNew;
         
         if (!pNew->pNext)
            pTail = pNew;

         numElements++;
      }
      else
         push_back(t);
       
       return pNew;
   }

   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }

   std::cerr << numElements << std::endl;
}

/***********************************************************
 *                       FIND()
 * Returns a pointer to the node that contains a desired
 *      data member
 **********************************************************/
template <class T>
typename list <T> :: iterator list <T> :: find(const T & t)
{
    for (iterator p = pHead; p; p++)
    {
        if (p->data == t)
            return p;
    }
    return NULL;
}


/*************************************************
 *                   ERASE()
 *  Removes an item where the passed in Iterator
 *      is pointing to
 ************************************************/
template <class T>
void list <T> :: erase(iterator & it) throw(const char *)
{    
    if (it == end())
        return;
    
    if (it.p->pPrev)
        it.p->pPrev->pNext = it.p->pNext;
    if (it.p->pNext)
        it.p->pNext->pPrev = it.p->pPrev;
            
    if (!it.p->pPrev)
       pHead = it.p->pNext;
    if (!it.p->pNext)
       pTail = it.p->pPrev;
    
    numElements--;
    delete it.p;
}

/*************************************************
 *                   FREEDATA()
 *  Erases all Nodes
 ************************************************/
template <class T>
void list <T> :: freeData(Node * & pHead)
{
    Node * pDelete;
    while (pHead != NULL)
    {
        pDelete = pHead;
        pHead = pHead->pNext;
        delete pDelete;
    }
}

}

#endif /* list_h */
