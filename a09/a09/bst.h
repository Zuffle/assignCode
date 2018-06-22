/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother Kirby, CS 235
 * Author:
 *    Taylor Williams, Justin Parry, Lu Yuan Ting
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H
#include "stack.h"
#include <iostream>
using namespace std;
using namespace custom;

//namespace custom
//{

template <class T>
class iterator;

template <class T>
class BNode;

/*****************************************************************
 * CLASS : BST : Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
public:
   //********** CLASSES **********//
   class BNode;
   class iterator;
   
   //********** CONSTRUCTORS **********//
   // default constructor
   BST() : root(NULL), numElements(0) {};
   
   // non-default constructor
   BST(const BST & rhs);
   
   // destructor
   ~BST();
   
   //********** OPERATORS **********//
   // assignment operator
   BST & operator = (const BST & rhs) throw (const char *)
   {
      root = copyBTree(rhs.root);
      numElements = rhs.numElements;
      return *this;
   }
   
   //********** METHODS **********//
   // size: return number element in BST
   int size()   { return numElements;      }
   
   // check if BST is empty
   bool empty() { return numElements == 0; }
   
   // clear all things in BST
   void clear()
   {
      deleteTree(this->root);
      numElements = 0;
   }
   
   // add item to BST
   void insert(const T & t) throw (const char * );
   
   // erase an item
   void erase(iterator & it);
   
   // find a given item
   iterator find(const T & t);
   
   // begin and end
   iterator begin() const;
   iterator end() const { return iterator(NULL); }
   iterator rbegin() const;
   iterator rend() const { return iterator(NULL); }
   
private:
   //********** MEMBERS **********//
   BNode * root;
   int numElements;
   
   //********** METHODS **********//
   // copy a Binary tree
   BNode * copyBTree(const BNode * pSrc) throw (const char *);
   
   // delete a binary tree
   void deleteTree(BNode * & pNode);
};

/*****************************************************************
 * BST - COPY CONSTRUCTOR : Creates a new BST as a copy of another
 *****************************************************************/
template <class T>
BST <T> :: BST(const BST <T> & rhs)
{
   // when root is not empty
   if (rhs.root != NULL)
   {
      // copy over everything from rhs
      root        = copyBTree(rhs.root);
      numElements = rhs.numElements;
   }
   // otherwise, set o and NULL to lhs
   else
   {
      root        = NULL;
      numElements = 0;
   }
}

/*****************************************************************
 * BST - DESTRUCTOR : Deletes a BST
 *****************************************************************/
template <class T>
BST <T> :: ~BST()
{
   if (root != NULL)
      deleteTree(this->root);
}

/********************************************************************
 * BST - COPYBTREE() : Makes a copy of the Binary Tree whose head was
 *  passed in
 ********************************************************************/
template <class T>
typename BST <T> :: BNode * BST <T> :: copyBTree(const BNode * pSrc) throw (const char *)
{
   if (pSrc == NULL)
      return NULL;
   try
   {
   BNode * pDestination = new BNode (pSrc->data);
   
   pDestination->pLeft = copyBTree(pSrc->pLeft);
   if (pDestination->pLeft != NULL)
      pDestination->pLeft->pParent = pDestination;
      
      pDestination->pRight = copyBTree(pSrc->pRight);
      if (pDestination->pRight != NULL)
         pDestination->pRight->pParent = pDestination;
         
         return pDestination;
   }
   
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate a node";
   }
}

/********************************************************************
 * BST - DELETETREE() : Deletes the BST
 ********************************************************************/
template <class T>
void BST <T> :: deleteTree(BNode * & pNode)
{
   if (pNode == NULL)
      return;
   deleteTree(pNode->pLeft);
   deleteTree(pNode->pRight);
   delete pNode;
   pNode = NULL;
}

/*************************************************
 * BST :: ERASE
 * ERASE a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> :: erase(iterator & it)
{
   //************ NO CHILD ************//
   BNode * temp = it.getNode();
   if (temp->pRight == NULL && temp->pLeft == NULL)
   {
      if (temp->pParent != NULL && temp->pParent->pLeft == it.getNode())
      {
         temp->pParent->pLeft = NULL;
      }
      else if (temp->pParent != NULL && temp->pParent->pRight == it.getNode())
      {
         temp->pParent->pRight = NULL;
      }
      delete temp;
      temp = NULL;
   }
   //************ JUAN CHILD ************//
   else if (temp->pRight == NULL && temp->pLeft != NULL)
   {
      temp->pLeft->pParent = temp->pParent;
      if (temp->pParent != NULL && temp->pParent->pRight == it.getNode())
      {
         temp->pParent->pRight = temp->pLeft;
      }
      if (temp->pParent != NULL && temp->pParent->pLeft == it.getNode())
      {
         temp->pParent->pLeft = temp->pLeft;
      }
      delete temp;
      temp = NULL;
   }
   else if (temp->pLeft == NULL && temp->pRight != NULL)
   {
      temp->pRight->pParent = temp->pParent;
      if (temp->pParent != NULL && temp->pParent->pRight == it.getNode())
      {
         temp->pParent->pRight = temp->pRight;
      }
      if (temp->pParent != NULL && temp->pParent->pLeft == it.getNode())
      {
         temp->pParent->pLeft = temp->pRight;
      }
      delete temp;
      temp = NULL;
   }
   //************ TWO CHILDREN ************//
   else if (temp->pLeft != NULL && temp->pRight != NULL)
   {
      BNode * ioSuccesser = temp;
      ioSuccesser = ioSuccesser->pRight;
      // Find the in-order successor
      while (ioSuccesser->pLeft)
      {
         ioSuccesser = ioSuccesser->pLeft;
      }
      temp->data = ioSuccesser->data;
      ioSuccesser->pParent->pLeft = ioSuccesser->pRight;
      if (ioSuccesser->pRight != NULL)
      {
         ioSuccesser->pRight->pParent = ioSuccesser->pParent;
      }
      delete ioSuccesser;
      ioSuccesser = NULL;
   }
}

/********************************************************************
 * BST - INSERT() : Inserts an item into the BST
 ********************************************************************/
template <class T>
void BST <T> :: insert(const T & t) throw (const char * )
{
   BNode * temp = root;
   bool inserted = false;
   try
   {
      if (this->empty())
      {
         BNode * newNode = new BNode (t);
         numElements++;
         this->root = newNode;
      }
      else
      {
         while (inserted == false)
         {
            if (t <= temp->data && temp->pLeft != NULL)
            {
               temp = temp->pLeft;
            }
            else if (t > temp->data && temp->pRight != NULL)
            {
               temp = temp->pRight;
            }
            else if (t <= temp->data && temp->pLeft == NULL)
            {
               BNode * newNode = new BNode (t);
               temp->pLeft = newNode;
               newNode->pParent = temp;
               numElements++;
               inserted = true;
            }
            else if (t > temp->data && temp->pRight == NULL)
            {
               BNode * newNode = new BNode (t);
               temp->pRight = newNode;
               newNode->pParent = temp;
               numElements++;
               inserted = true;
            }
         }
      }
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/****************************************************
 * BST :: FIND
 * Return the node corresponding to a given value
 ****************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: find(const T & t)
{
   BNode * temp = root;
   
   bool found = false;
   while (found == false)
   {
      if (temp == NULL)
      {
         found = true;
         return end();
      }
      if (t < temp->data)
      {
         temp = temp->pLeft;
      }
      else if (t > temp->data)
      {
         temp = temp->pRight;
      }
      else if (t == temp->data)
      {
         BST <T> :: iterator * it = new BST <T> :: iterator (temp);
         found = true;
         return * it;
      }
   }
   return NULL;
}


/*****************************************************************
 * CLASS : BINARY NODE : A single node in a binary tree
 *****************************************************************/
template <class T>
class BST <T> :: BNode
{
public:
   //********** CONSTRUCTORS *********//
   BNode() : data(T()), pParent(NULL), pLeft (NULL), pRight(NULL) {}
   BNode(const T & t) : data(t), pParent(NULL), pLeft (NULL), pRight(NULL) {}
   
   //*********** OPERATORS ***********//
   BNode & operator = (BNode & rhs) throw (const char *);
   
   //*********** MEMBERS ***********//
   T data;
   BNode * pParent;
   BNode * pLeft;
   BNode * pRight;
};

/*********************************************************************
 * BNODE - ASSIGNMENT OPERATOR : Copies a BNode using the '=' operator
 *********************************************************************/
template <class T>
typename BST <T> :: BNode & BST <T> :: BNode :: operator = (BNode & rhs) throw (const char *)
{
   this->data = rhs->data;
   this->pParent = NULL;
   this->pRight = NULL;
   this->pLeft = NULL;
   
   return *this;
}

/********************************************************************
 * CLASS : ITERATOR : This will define an iterator to traverse a list
 ********************************************************************/
template <class T>
class BST <T> :: iterator
{
public:
   //********** CONSTRUCTORS *********//
   // default constructor
   iterator(BNode * p = NULL)      { pNode.push(p);     }
   
   // non-default constructor
   iterator(stack <BNode*> & s)    { pNode = s;         }
   
   // copy constructor
   iterator(const iterator & rhs)  { pNode = rhs.pNode; }
   
   //*********** OPERATORS ***********//
   // assignment operator
   iterator & operator =(const iterator & rhs)
   {
      // assign rhs to pNode
      pNode = rhs.pNode;
      return *this;
   }
   
   // is equal operator
   bool operator == (const iterator & rhs)
   {
      // only compare the leaf nodes
      return rhs.pNode.top() == this->pNode.top();
   }
   
   // is not equal operator
   bool operator != (const iterator & rhs)
   {
      // only compare the leaf of nodes
      return rhs.pNode.top() != this->pNode.top();
   }
   
   // de-reference operator
   T & operator * ()
   {
      return pNode.top()->data;
   }
   
   // increment
   iterator & operator ++ ();
   iterator operator ++ (int postfix)
   {
      iterator itReturn = *this;
      ++(*this);
      return itReturn;
   }
   
   // decrement
   iterator & operator -- ();
   iterator operator -- (int postfix)
   {
      iterator itReturn = *this;
      --(*this);
      return itReturn;
   }
   
   // get the node pointer
   BNode * getNode() { return pNode.top(); }
   
private:
   // a stack of nodes
   stack <BNode*> pNode;
   
   
};

/********************************************************************
 * ITERATOR - DECREMENT PREFIX : Advance by one
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 ********************************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
{
   // do nothing if we have nothing
   if (NULL == pNode.top())
      return *this;
   
   // if there is a left node, take it
   if (NULL != pNode.top()->pLeft)
   {
      // go left
      pNode.push(pNode.top()->pLeft);
      
      // jig right - there might be more right-most children
      while (pNode.top()->pRight)
         pNode.push(pNode.top()->pRight);
      return *this;
   }
   
   // there are no left children, the right are done
   assert(NULL == pNode.top()->pLeft);
   BNode * pSave = pNode.top();
   
   // go up
   pNode.push(pNode.top()->pParent);
   
   // if the parent is the NULL, we are done!
   if (NULL == pNode.top())
      return *this;
   
   // if we are the right-child, got to the parent.
   if (pSave == pNode.top()->pRight)
      return *this;
   
   // we are the left-child, go up as long as we are the left child!
   while (NULL != pNode.top() && pSave == pNode.top()->pLeft)
   {
      pSave = pNode.top();
      pNode.push(pNode.top()->pParent);
   }
   
   return *this;
}

/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator ++ ()
{
   // do nothing if we have nothing
   if (pNode.top() == NULL)
      return *this;
   
   // if there is a right node, take it
   if (pNode.top()->pRight != NULL)
   {
      pNode.push(pNode.top()->pRight);
      
      // there might be more left-most children
      while (pNode.top()->pLeft)
         pNode.push(pNode.top()->pLeft);
      return *this;
   }
   
   // there are no right children, the left are done
   assert(pNode.top()->pRight == NULL);
   BNode * pSave = pNode.top();
   pNode.pop();
   
   // if the parent is the NULL, we are done!
   if (NULL == pNode.top())
      return *this;
   
   // if we are the left-child, got to the parent.
   if (pSave == pNode.top()->pLeft)
      return *this;
   
   // we are the right-child, go up as long as we are the right child!
   while (pNode.top() != NULL && pSave == pNode.top()->pRight)
   {
      pSave = pNode.top();
      pNode.pop();
   }
   
   return *this;
}

/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: begin() const
{
   stack < BNode * > nodes;
   
   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);
   
   return iterator(nodes);
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: rbegin() const
{
   stack <BNode*> nodes;
   
   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);
   
   return iterator(nodes);
}

//} // namespace custom

#endif // BST_H
