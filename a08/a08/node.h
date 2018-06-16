//
//  node.h
//  Week 6
//
//  Created by Taylor Williams on 5/26/18.
//  Copyright © 2018 Taylor Williams. All rights reserved.
//

#ifndef node_h
#define node_h

#include <iostream>
using namespace std;


/***********************************************************
 *                     CLASS: NODE
 * Defines a simple Node class
 **********************************************************/
template <class T>
class Node
{
public:
    /*** VARIABLES ***/
    T data;                         // The data in the Node
    Node <T> * pNext;               // Pointer to the next item in the list
    Node <T> * pPrev;               // Pointer to the previoud item in the list
    
    /*** CONSTRUCTORS ***/
    Node () : data(T()), pNext(NULL), pPrev(NULL) {}
    Node (const T & t) : data(t), pNext(NULL), pPrev(NULL) {}
};

/***********************************************************
 *                       INSERT()
 * This will insert an item into the linked list
 **********************************************************/
template <class T>
Node <T> * insert(Node <T> * & pNode, const T & t, bool after = false) throw (const char *)
{
    Node <T> * pNew = new Node <T> (t);
    
    if (pNode != NULL && after == false)
    {
        pNew->pNext  = pNode;
        pNew->pPrev  = pNode->pPrev;
        pNode->pPrev = pNew;
        if (pNew->pPrev)
            pNew->pPrev->pNext = pNew;
    }
    if (pNode != NULL && after == true)
    {
        pNew->pNext = pNode->pNext;
        pNew->pPrev = pNode;
        pNode->pNext = pNew;
        if (pNew->pNext)
            pNew->pNext->pPrev = pNew;
    }
    return pNew;
}

/***********************************************************
 *                       FIND()
 * Returns a pointer to the node that contains a desired
 *      data member
 **********************************************************/
template <class T>
Node <T> * find(Node <T> * pHead, const T & t)
{
    for (Node <T> * p = pHead; p; p = p->pNext)
    {
        if (p->data == t)
            return p;
    }
    return NULL;
}

/***********************************************************
 *                      OPERATOR: <<
 * Overloads the << Operator to display the linked list
 **********************************************************/
template <class T>
ostream & operator << (ostream & out, const Node <T> * pHead)
{
    bool first = true;
    for (const Node <T> * p = pHead; p; p = p->pNext)
    {
        if (first)
        {
            out << p->data;
            first = false;
        }
        else
            out << ", " << p->data;
    }
    return out;
}

/***********************************************************
 *                      FREEDATA()
 * This will empty all of the data and set the head to NULL
 **********************************************************/
template <class T>
void freeData(Node <T> * & pHead)
{
    Node <T> * pDelete;
    while (pHead != NULL)
    {
        pDelete = pHead;
        pHead = pHead->pNext;
        delete pDelete;
    }
}

/***********************************************************
 *                       REMOVE()
 * Remove an item from the linked list
 **********************************************************/
template <class T>
Node <T> * remove(const Node <T> * pRemove)
{
    Node <T> * pReturn;
    
    if (pRemove == NULL)
        return NULL;
    
    if (pRemove->pPrev)
        pRemove->pPrev->pNext = pRemove->pNext;
    if (pRemove->pNext)
        pRemove->pNext->pPrev = pRemove->pPrev;
    
    if (pRemove->pPrev)
        pReturn = pRemove->pPrev;
    else
        pReturn = pRemove->pNext;
    
    delete pRemove;
    return pReturn;
}

/***********************************************************
 *                       COPY()
 * This will copy over all the information into a new list
 **********************************************************/
template <class T>
Node <T> * copy(Node <T> * pSource) throw (const char *)
{
    Node <T> * pDestination = new Node <T> (pSource->data);
    Node <T> * pSrc         = pSource;
    Node <T> * pDes         = pDestination;
    
    pSrc = pSrc->pNext;
    
    while (pSrc != NULL)
    {
        insert(pDes, pSrc->data, true);
        pDes = pDes->pNext;
        pSrc = pSrc->pNext;
    }
    
    return pDestination;
}

#endif /* node_h */
