/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother <your instructor name here>, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"
#include <iostream>

namespace custom
{
//
//   template <class T>
//   class iterator;
   
   template <class T>
   class BST
   {
   public:
      //********** CLASS **********//
      class BNode;
      class iterator;
      
      //********** CONSTRUCTORS **********//
      BST() : root(NULL), numElements(0) {};
      BST(const BST & rhs)
      {
         if (rhs.root != NULL)
         {
            root        = copyBTree(rhs.root);
            numElements = rhs.numElements;
         }
         else
         {
            root        = NULL;
            numElements = 0;
         }
      }
      
      
      ~BST()
      {
         destroyRecursive(root);
      }
      
      //********** OPERATORS **********//
      BST & operator = (const BST & rhs) throw (const char *)
      {
         root = copyBTree(rhs.root);
         numElements = rhs.numElements;
         return *this;
      }
      
      //********** METHODS **********//
      int size()   { return numElements;      }
      bool empty() { return numElements == 0; }
      
   private:
      BNode * copyBTree(const BNode * pSrc) throw (const char *);
      BNode * root;
      
      void destroyRecursive(BNode * node)
      {
         if (node)
         {
            destroyRecursive(node->pLeft);
            destroyRecursive(node->pRight);
            delete node;
         }
      }
      
      int numElements;
   };
   
   /*****************************************************************
    * COPYBTREE() : Makes a copy of the Binary Tree whose head was
    *  passed in
    *****************************************************************/
   template <class T>
   typename BST <T> :: BNode * BST <T> :: copyBTree(const BST <T> :: BNode * pSrc) throw (const char *)
   {
      if (pSrc == NULL)
         return NULL;
      
      BST <T> :: BNode * pDestination = new BNode (pSrc->data);

      pDestination->pLeft = copyBTree(pSrc->pLeft);
      if (pDestination->pLeft != NULL)
         pDestination->pLeft->pParent = pDestination;
         
         pDestination->pRight = copyBTree(pSrc->pRight);
         if (pDestination->pRight != NULL)
            pDestination->pRight->pParent = pDestination;
            
            return pDestination;
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
   typename BST <T> :: BNode & BST <T> :: BNode :: operator = (BST <T> :: BNode & rhs) throw (const char *)
   {
      this->data = rhs->data;
      this->pParent = NULL;
      this->pRight = NULL;
      this->pLeft = NULL;
      
      return *this;
   }

   /**********************************************
    *              CLASS: ITERATOR
    * This will define an iterator to traverse a
    *  list
    *********************************************/
   template <class T>
   class BST <T> :: iterator
   {
   public:
      /***************************************************
       * CONSTRUCTORS, DESTRUCTOR AND ASSIGNMENT OPERATOR
       ***************************************************/
      iterator() : pNode(NULL) {}
      iterator(BNode * p) {this->pNode = p; }
      iterator(const iterator & rhs) { this->pNode = rhs.pNode; }
      
      iterator & operator = (const iterator & rhs)
      {
         this -> pNode = rhs.pNode;
         return *this;
      }
      bool operator != (const iterator & rhs) const {return (rhs.pNode->data != this->pNode->data); }
      bool operator == (const iterator & rhs) const {return (rhs.pNode->data == this->pNode->data); }
      BST <T> :: iterator & operator ++ ();
      BST <T> :: iterator & operator -- ();
      
   private:
      BST <T> :: BNode * pNode;
   };
   
   /**************************************************
    * BST ITERATOR :: INCREMENT PREFIX
    *     advance by one.
    *************************************************/
   template <class T>
   typename BST <T> :: iterator & BST <T> :: iterator :: operator ++ ()
   {
      // don't do anyting if we have nothing
      if (NULL == pNode)
      {
         return *this;
      }
      
      if (NULL != pNode->pRight)
      {
         // go right
         pNode = pNode->pRight;
         
         //jig left
         while (pNode->pLeft)
         {
            pNode = pNode->pLeft;
         }
         
         return *this;
      }
      
      // should have no right children, left is done
      assert(NULL == pNode->pRight);
      BNode * pSave = pNode;
      
      // go up
      pNode = pNode->pParent;
      
      // if parent is NULL we're done
      if (NULL == pNode)
      {
         return *this;
      }
      
      //if we are the left child with no right child, we go up
      if (pSave == pNode->pLeft)
      {
         return *this;
      }
      
      // we know we are the right child and we're the right child we need to go to grandparent
      
      while (NULL != pNode && pSave == pNode->pRight)
      {
         pSave = pNode;
         pNode = pNode->pParent;
      }
      
      return *this;
      
   }
   
   /**************************************************
    * BST ITERATOR :: DECREMENT PREFIX
    *     advance by one.
    * Author:      Br. Helfrich
    * Performance: O(log n) though O(1) in the common case
    *************************************************/
   template <class T>
   typename BST <T> :: iterator & BST <T> :: iterator :: operator -- ()
   {
      // do nothing if we have nothing
      if (NULL == pNode)
         return *this;
      
      // if there is a left node, take it
      if (NULL != pNode->pLeft)
      {
         // go left
         pNode = pNode->pLeft;
         
         // jig right - there might be more right-most children
         while (pNode->pRight)
            pNode = pNode->pRight;
         return *this;
      }
      
      // there are no left children, the right are done
      assert(NULL == pNode->pLeft);
      BNode * pSave = pNode;
      
      // go up
      pNode = pNode->pParent;
      
      // if the parent is the NULL, we are done!
      if (NULL == pNode)
         return *this;
      
      // if we are the right-child, got to the parent.
      if (pSave == pNode->pRight)
         return *this;
      
      // we are the left-child, go up as long as we are the left child!
      while (NULL != pNode && pSave == pNode->pLeft)
      {
         pSave = pNode;
         pNode = pNode->pParent;
      }
      
      return *this;
   }
   
} // namespace custom

#endif // BST_H
