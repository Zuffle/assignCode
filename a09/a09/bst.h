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

namespace custom
{
   
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
      // Checks if there is anything to delete
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
      // Recursive function to traverse every node
      if (pSrc == NULL)
         return NULL;
      try
      {
         // Create new Node
         BNode * pDestination = new BNode (pSrc->data);
         pDestination->isRed  = pSrc->isRed;
         
         // Go down the left side
         pDestination->pLeft = copyBTree(pSrc->pLeft);
         if (pDestination->pLeft != NULL)
         {
            pDestination->pLeft->pParent = pDestination;
         }
         // Then the right side
         pDestination->pRight = copyBTree(pSrc->pRight);
         if (pDestination->pRight != NULL)
         {
            pDestination->pRight->pParent = pDestination;
         }
         
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
      // Another recursive function
      if (pNode == NULL)
         return;
      // Go down the left side
      deleteTree(pNode->pLeft);
      // Then the right side
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
      //************ ONE CHILD ************//
      // If the child is on the left
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
      // If the child is on the right
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
      // Create temp pointer to node
      BNode * temp = root;
      bool inserted = false; // End when inserted
      try
      {
         if (this->empty())
         {
            // If empty, just place in root
            BNode * newNode = new BNode (t);
            numElements++;
            this->root = newNode;
            root->balance();
         }
         else
         {
            // Find place until it is inserted
            while (inserted == false)
            {
               // If less than
               if (t <= temp->data && temp->pLeft != NULL)
               {
                  temp = temp->pLeft;
               }
               // If greater than
               else if (t > temp->data && temp->pRight != NULL)
               {
                  temp = temp->pRight;
               }
               // If less than && last stop
               else if (t <= temp->data && temp->pLeft == NULL)
               {
                  BNode * newNode = new BNode (t);
                  temp->pLeft = newNode;
                  newNode->pParent = temp;
                  numElements++;
                  inserted = true;
               }
               // If greater than && last stop
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
      // Pointer to nodes
      BNode * temp = root;
      
      bool found = false;
      while (found == false)
      {
         // If it is not found, return NULL
         if (temp == NULL)
         {
            found = true;
            return end();
         }
         // Go left if t is less than
         if (t < temp->data)
         {
            temp = temp->pLeft;
         }
         // go right if greater than
         else if (t > temp->data)
         {
            temp = temp->pRight;
         }
         // Return if equal
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
      BNode() : data(T()), pParent(NULL), pLeft (NULL), pRight(NULL), isRed(true) {}            // when a new node is added it is red at first
      BNode(const T & t) : data(t), pParent(NULL), pLeft (NULL), pRight(NULL), isRed(true) {}
      
      //*********** OPERATORS ***********//
      BNode & operator = (BNode & rhs) throw (const char *);
      
      //*********** METHODS ***********//
      
      // balances the tree
      void balance();
      
      // debug methods
      int findDepth() const;
      void verifyRedBlack(int depth) const;
      void verifyBTree() const;
      
      
      //*********** MEMBERS ***********//
      T data;
      BNode * pParent;
      BNode * pLeft;
      BNode * pRight;
      bool isRed;
   };
   
   /*********************************************************************
    * BNODE - ASSIGNMENT OPERATOR : Copies a BNode using the '=' operator
    *********************************************************************/
   template <class T>
   typename BST <T> :: BNode & BST <T> :: BNode :: operator = (BNode & rhs) throw (const char *)
   {
      this->data = rhs->data; // Copies the data into a default BNode
      this->pParent = NULL;
      this->pRight = NULL;
      this->pLeft = NULL;
      
      return *this;
   }
   
   /*********************************************************************
    * BNODE - BALANCE : Balances the tree with red-black logic
    *********************************************************************/
   template <class T>
   void BST <T> :: BNode :: balance()
   {
      assert(isRed == true);                 // default value of isRed should be true
      
      // if it is the root
      if (pParent == NULL)
      {
         assert(isRed == true);              // default value of isRed should be true
         isRed = false;                      // now it is black
         return;
      }
      
      // if parent is black nothing to do
      if (pParent->isRed == false)
      {
         return;
      }
      
      // if we are this far we must have a grandparent
      assert(pParent->pParent);
      
      // does it have to be black?
      
      
      if (pParent->isRed)
      {
         
         // CASE 3
         {
            // if the parent is red, aunt exists and is red, may need more balancing after if greatgrandparent is also red
            // if parent is the left child in case 3
            if (pParent->pParent->pLeft == pParent && pParent->pParent->pRight->isRed == true)
            {
               // make parent black
               pParent->isRed = false;
               
               // make aunt black
               pParent->pParent->pRight->isRed = false;
               
               // make grandparent red;
               pParent->pParent->isRed = true;
            
               
               // check if we need more balancing
               if (pParent->pParent->pParent->isRed)
               {
                  // we rebalance with the grandparent I THINK
                  pParent->pParent->balance();
               }
            } // if parent is left child
            
            // if parent is right in case 3
            if (pParent->pParent->pRight == pParent && pParent->pParent->pLeft->isRed == true)
            {
               // make parent black
               pParent->isRed = false;
               
               // make aunt black
               pParent->pParent->pLeft->isRed = false;
               
               // make grandparent red;
               pParent->pParent->isRed = true;
               
               // check if we need more balancing
               if (pParent->pParent->pParent->isRed)
               {
                  // we rebalance with the grandparent I THINK
                  pParent->pParent->balance();
               }
               
            } // if for parent is the right child
         }
         
         // CASE 4 if aunt is black or does not exist, I don't think we really need to check for the aunt
         {
            // a) node is left of parent and parent is left of grandparent
            if (pParent->pParent->pLeft == pParent && pParent->pLeft == this)
            {
               // parent goes to black
               pParent->isRed = false;
               
               // grandparent goes to red
               pParent->pParent->isRed = true;
               
               // make a temp pointer to a BNode in case we have a sibling
               BNode * pSib = NULL;
               
               // check for a sibling and if there is set it to the temp pointer pSib
               if (pParent->pRight)
               {
                  pSib = pParent->pRight;
               }
               
               // start rotating right, gotta check
               if (pParent->pParent->pParent)
               {
                  // set grandparent to right child of parent
                  pParent->pRight = pParent->pParent;
                  
                  // set parent's parent to grandparent's old parent
                  pParent->pParent = pParent->pRight->pParent;
                  
                  // set the grandparent's new parent to current parent
                  pParent->pRight->pParent = pParent;
                  
                  // if we had a sibling put into the temp pSib then move the sibling over to the grandparent's right child
                  if (pSib)
                  {
                     pParent->pRight->pLeft = pSib;
                  }
               }
               
               else
               {
                  // make grandparent the right child
                  pParent->pRight = pParent->pParent;
                  
                  // since grandparent was the root (parent was NULL) set parent's parent to NULL
                  pParent->pParent = NULL;
                  
                  // set the grandparent's new parent to current parent
                  pParent->pRight->pParent = pParent;
                  
                  // if we had a sibling put into the temp pSib then move the sibling over to the grandparent's right child
                  if (pSib)
                  {
                     pParent->pRight->pLeft = pSib;
                  }
               }
            } // a) node is left of parent and parent is left of grandparent
            
            // b) node is right of parent and parent is right of grandparent
            if (pParent->pParent->pRight == pParent && pParent->pRight == this)
            {
               // parent goes to black
               pParent->isRed = false;
               
               // grandparent goes to red
               pParent->pParent->isRed = true;
               
               // make a temp pointer to a BNode in case we have a sibling
               BNode * pSib = NULL;
               
               // check for a sibling and if there is set it to the temp pointer pSib
               if (pParent->pLeft)
               {
                  pSib = pParent->pLeft;
               }
               
               // start rotating right, gotta check
               if (pParent->pParent->pParent)
               {
                  // set grandparent to left child of parent
                  pParent->pLeft = pParent->pParent;
                  
                  // set grandparent's parent to parent's parent
                  pParent->pParent = pParent->pLeft->pParent;
                  
                  // set the grandparent's new parent to current parent
                  pParent->pLeft->pParent = pParent;
                  
                  // if we had a sibling put into the temp pSib then move the sibling over to the grandparent's left child
                  if (pSib)
                  {
                     pParent->pLeft->pRight = pSib;
                  }
               }
               
               else
               {
                  // make grandparent the left child
                  pParent->pLeft = pParent->pParent;
                  
                  // since grandparent was the root (parent was NULL) set parent's parent to NULL
                  pParent->pParent = NULL;
                  
                  // set the grandparent's new parent to current parent
                  pParent->pLeft->pParent = pParent;
                  
                  // if we had a sibling put into the temp pSib then move the sibling over to the grandparent's right child
                  if (pSib)
                  {
                     pParent->pLeft->pRight = pSib;
                  }
               }
            } // b) node is right of parent and parent is right of grandparent
            
            // c) node is right of parent and parent is left of grandparent
            if (pParent->pRight == this && pParent->pParent->pLeft == pParent)
            {
               // check to see if we got any children
               if (pLeft)
               {
                  // if we do have a left child it becomes the right child of parent
                  pParent->pRight = pLeft;
               }

               if (pRight)
               {
                  // if we do have a right child it becomes the left child of grandparent
                  pParent->pParent->pLeft = pRight;
               }
               
               //set this node to the head of this subtree (where grandparent is)
               
               // set grandparent to right child
               pRight = pParent->pParent;
            
               // set parent to left child
               pLeft = pParent;
               
               // now set grandparent's (now in the right child pointer) parent as this node's new parent if it is not NULL
               if (pRight->pParent == NULL)
               {
                  pParent = NULL;
               }
               
               else
               {
                  pParent = pRight->pParent;
               }
               
               // check which child the grandparent was
               if (pRight->pParent->pLeft == pRight)
               {
                  pRight->pParent->pLeft = this;
               }
               
               else if (pRight->pParent->pRight == pRight)
               {
                  pRight->pParent->pRight = this;
               }
               
               // set parent's new parent to this node
               pRight->pParent = this;
               
               // set grandparent's new parent to this node
               pLeft->pParent = this;
               
            } // c) node is right of parent and parent is left of grandparent
            
            // d) node it left of parent and parent is right of grandparent
            if (pParent->pLeft == this && pParent->pParent->pRight == pParent)
            {
                // check to see if we got any children
               if (pLeft)
               {
                  // if we do have a left child it becomes the right child of grandparent
                  pParent->pParent->pRight = pLeft;
               }
               
               if (pRight)
               {
                  // if we do have a right child it becomes the left child of grandparent
                  pParent->pLeft = pRight;
               }
               
               // set this node to the head of this subtree (where grandparent is)
               
               // set grandparent to left child
               pLeft = pParent->pParent;
               
               // set parent to right child
               pRight = pParent;
               
               // now set grandparent's (now in the left child pointer) parent as this node's new parent if it is not NULL
               if (pLeft->pParent == NULL)
               {
                  pParent = NULL;
               }
               
               else
               {
                  pParent = pLeft->pParent;
               }
               
               // check which child the grandparent was
               if (pLeft->pParent->pLeft == pLeft)
               {
                  pLeft->pParent->pLeft = this;
               }
               
               else if (pLeft->pParent->pRight == pLeft)
               {
                  pLeft->pParent->pRight = this;
               }
               
               // set parent's new parent to this node
               pRight->pParent = this;
               
               // set grandparent's new parent to this node
               pLeft->pParent = this;
               
            } // d) node it left of parent and parent is right of grandparent
            
         } // CASE 4 if aunt is black or does not exist, I don't think we really need to check for the aunt
      } // if parent is red
      
   }

   /****************************************************
    * BINARY NODE :: FIND DEPTH
    * Find the depth of the black nodes. This is useful for
    * verifying that a given red-black tree is valid
    * Author: Br. Helfrich
    ****************************************************/
   
   template <class T>
   int BST <T> :: BNode :: findDepth() const
   {
      // if there are no children, the depth is ourselves
      if (pRight == NULL && pLeft == NULL)
         return (isRed ? 0 : 1);
      
      // if there is a right child, go that way
      if (pRight != NULL)
         return (isRed ? 0 : 1) + pRight->findDepth();
      else
         return (isRed ? 0 : 1) + pLeft->findDepth();
   }
   
   /****************************************************
    * BINARY NODE :: VERIFY RED BLACK
    * Do all four red-black rules work here?
    * Author: Br. Helfrich
    ***************************************************/
   template <class T>
   void BST <T> :: BNode :: verifyRedBlack(int depth) const
   {
      depth -= (isRed == false) ? 1 : 0;
      
      // Rule a) Every node is either red or black
      assert(isRed == true || isRed == false); // this feels silly
      
      // Rule b) The root is black
      if (pParent == NULL)
         assert(isRed == false);
      
      // Rule c) Red nodes have black children
      if (isRed == true)
      {
         if (pLeft != NULL)
            assert(pLeft->isRed == false);
         if (pRight != NULL)
            assert(pRight->isRed == false);
      }
      
      // Rule d) Every path from a leaf to the root has the same # of black nodes
      if (pLeft == NULL && pRight && NULL)
         assert(depth == 0);
      if (pLeft != NULL)
         pLeft->verifyRedBlack(depth);
      if (pRight != NULL)
         pRight->verifyRedBlack(depth);
   }
   
   /******************************************************
    * VERIFY B TREE
    * Verify that the tree is correctly formed
    * Author: Br. Helfrich
    ******************************************************/
   template <class T>
   void BST <T> :: BNode :: verifyBTree() const
   {
      // check parent
      if (pParent)
         assert(pParent->pLeft == this || pParent->pRight == this);
      
      // check left
      if (pLeft)
      {
         assert(pLeft->data <= data);
         assert(pLeft->pParent == this);
         pLeft->verifyBTree();
      }
      
      // check right
      if (pRight)
      {
         assert(pRight->data >= data);
         assert(pRight->pParent == this);
         pRight->verifyBTree();
      }
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
      
      // Push on nothing, then the root, then go all the way to the left
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
      
      // Push on nothing, then the root, then go all the way to the right
      nodes.push(NULL);
      nodes.push(root);
      while (nodes.top() != NULL && nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      
      return iterator(nodes);
   }
   
} // namespace custom

#endif // BST_H
