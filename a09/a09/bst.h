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

   template <class T>
   class iterator;
   
   template <class T>
   class BST
   {
   public:
      //********** CLASS **********//
      class BNode;
      class iterator;
      
      //********** CONSTRUCTORS **********//
      BST() : root(NULL), numElements(0) {};
      BST(const BST & rhs);
      ~BST();
      
      //********** OPERATORS **********//
      // size: return number element in BST
      BST & operator = (const BST & rhs) throw (const char *)
      {
         root = copyBTree(rhs.root);
         numElements = rhs.numElements;
         return *this;
      }
      
      //********** METHODS **********//
      
      int size()   { return numElements;      }
      
      // check if BST is empty
      bool empty() { return numElements == 0; }
      
      // clear all things in BST
      void clear()
      {
         deleteTree(this->root);
      }
      
      // add item to BST
      void insert(const T & t) throw (const char * );
      
      // remove item from BST
      void erase(iterator & it);
      
      // find an item in the BST
      iterator find(const T & t);
      
      //iterators for begin and end
      iterator begin()  { return iterator (root); }
      iterator end()    { return iterator(); }

   private:
      BNode * copyBTree(const BNode * pSrc) throw (const char *);
      BNode * root;
      int numElements;
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

   /********************************************************************
    * BST - ERASE() : Removes an item from the BST
    ********************************************************************/
   template <class T>
   void BST <T> :: erase(BST <T> :: iterator & it)
   {
      if (NULL == it->pLeft && NULL == it->pRight)
      {
         if (NULL != it->pParent && it->pParent->pRight == it)
         {
            it->pParent->pRight = NULL;
         }
         
         if (NULL != it->pParent && it->pParent->pLeft == it)
         {
            it->pParent->pLeft = NULL;
         }
         
         delete it;
      }
      
      else if (NULL == it->pRight && it->pLeft != NULL)
      {
         it->pLeft->pParent = it->pParent;
         
         if (NULL != it->pParent && it->pParent->pRight == it)
         {
            it->pParent->pRight = it->pLeft;
         }
         
         if (NULL != it->pParent && it->pParent->pLeft == it)
         {
            it->pParent->pLeft = it->pLeft;
         }
         
         delete it;
      }
      
      else if (NULL == it->pLeft && it->pRight != NULL)
      {
         it->pRight->pParent = it->pParent;
         
         if (NULL != it->pParent && it->pParent->pRight == it)
         {
            it->pParent->pRight = it->pRight;
         }
         
         if (NULL != it->pParent && it->pParent->pLeft == it)
         {
            it->pParent->pLeft = it->pRight;
         }
         
         delete it;
      }
      
      else
      {
         assert(it->pRight != NULL && it->pLeft != NULL);
         
         BST <T> :: iterator it2 = it;
         *it = *++it2;
         
         erase(it2);
      }
      
   }

   /********************************************************************
    * BST - FIND() : Finds the place in the BST with a certain value
    ********************************************************************/
   template <class T>
   typename BST <T> :: iterator BST <T> :: find(const T & t)
   {
      if (t < root)
      {
         BST <T> :: iterator it = begin();
         while (t != *it)
            it++;
         return it;
      }
      
      else
      {
         for(BST <T> :: iterator it(root->pRight); it != end(); ++it)
         {
            if (t == *it)
               return it;
         }  
      }
      
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
      //default constructor
      iterator() : pNode(NULL) {}
      
      // non- default constructor
      iterator(BNode * p) {this->pNode = p; }
      
      // copy constructor
      iterator(const iterator & rhs) { this->pNode = rhs.pNode; }
      
      //assignment operator
      iterator & operator = (const iterator & rhs)
      {
         this -> pNode = rhs.pNode;
         return *this;
      }
      
      bool operator != (const iterator & rhs) const {return (rhs.pNode != this->pNode); }
      bool operator == (const iterator & rhs) const {return (rhs.pNode == this->pNode); }
      iterator & operator ++ ();
      iterator & operator -- ();
      
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
