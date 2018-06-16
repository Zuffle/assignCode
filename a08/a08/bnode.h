//
//  bnode.h
//  Week 8
//
//  Created by Taylor Williams on 6/11/18.
//  Copyright © 2018 Taylor Williams. All rights reserved.
//

#ifndef bnode_h
#define bnode_h

#include "pair.h"

#include <iostream>
#include <cassert>
using namespace std;

/*****************************************************************
 * ClASS : BINARY NODE : A single node in a binary tree
 *****************************************************************/
template <class T>
class BNode
{
public:
    // CONSTRUCTORS //
    BNode() : data(T()), pParent(NULL), pLeft (NULL), pRight(NULL) {}
    BNode(const T & t) : data(t), pParent(NULL), pLeft (NULL), pRight(NULL) {}
    
    BNode & operator = (BNode & rhs) throw (const char *);
    
    
    // VARIABLES //
    T data;
    BNode <T> * pParent;
    BNode <T> * pLeft;
    BNode <T> * pRight;
};

/*****************************************************************
 * SIZE() : Returns the number of Nodes in the tree
 *****************************************************************/
template <class T>
int sizeBTree(const BNode <T> * pRoot)
{
    if (pRoot == NULL)  // Then there are no Nodes in the tree
        return 0;
    else                // Do a LVR traversal of the tree
        return sizeBTree(pRoot->pLeft) + 1 + sizeBTree(pRoot->pRight);
}

/*****************************************************************
 * ADDLEFT(New Node) : Adds a new Node to the tree to the left of
 *  the given location
 *****************************************************************/
template <class T>
void addLeft(BNode <T> * pNode, BNode <T> * pAdd)
{
    if (pAdd != NULL)
        pAdd->pParent = pNode;
    pNode->pLeft = pAdd;
}

/*****************************************************************
 * ADDRIGHT(New Node) : Adds a new Node to the tree to the right of
 *  the given location
 *****************************************************************/
template <class T>
void addRight(BNode <T> * pNode, BNode <T> * pAdd)
{
    if (pAdd != NULL)
        pAdd->pParent = pNode;
    pNode->pRight = pAdd;
}

/*****************************************************************
 * ADDLEFT(Value) : Adds a new Node to the tree to the left of
 *  the given location
 *****************************************************************/
template <class T>
void addLeft(BNode <T> * pNode, const T & t)
{
    BNode <T> * pAdd = new BNode <T> (t);
    pAdd->pParent    = pNode;
    pNode->pLeft     = pAdd;
}

/*****************************************************************
 * ADDRIGHT(Value) : Adds a new Node to the tree to the right of
 *  the given location
 *****************************************************************/
template <class T>
void addRight(BNode <T> * pNode, const T & t)
{
    BNode <T> * pAdd = new BNode <T> (t);
    pAdd->pParent    = pNode;
    pNode->pRight    = pAdd;
}

/*****************************************************************
 * COPYBTREE() : Makes a copy of the Binary Tree whose head was
 *  passed in
 *****************************************************************/
template <class T>
BNode <T> * copyBTree(const BNode <T> * pSrc) throw (const char *)
{
    if (pSrc == NULL)
        return NULL;
    
    BNode <T> * pDestination = new BNode <T> (pSrc->data);
    
    pDestination->pLeft = copyBTree(pSrc->pLeft);
    if (pDestination->pLeft != NULL)
        pDestination->pLeft->pParent = pDestination;
        
    pDestination->pRight = copyBTree(pSrc->pRight);
    if (pDestination->pRight != NULL)
        pDestination->pRight->pParent = pDestination;
        
    return pDestination;
}

/*****************************************************************
 * DELETEBTREE() : Deletes a Binary Tree whose head was passed in
 *****************************************************************/
template <class T>
void deleteBTree(BNode <T> * & pNode)
{
    if (pNode == NULL)
        return;
    deleteBTree(pNode->pLeft);
    deleteBTree(pNode->pRight);
    delete pNode;
    pNode = NULL;
}

/*****************************************************************
 * OPERATOR << (DISPLAY)
 *****************************************************************/
template <class T>
ostream & operator << (ostream & out, const BNode <T> * pHead)
{
    if (pHead == NULL)
        return out;
    
    cout << pHead->pLeft;
    out << pHead->data << " ";
    cout << pHead->pRight;
    return out;
}

/*****************************************************************
 * 
 *****************************************************************/
template <class T>
BNode <T> & BNode <T> :: operator = (BNode <T> & rhs) throw (const char *)
{
    this->data = rhs->data;
    this->pParent = NULL;
    this->pRight = NULL;
    this->pLeft = NULL;
    
    return *this;
}

#endif /* bnode_h */
