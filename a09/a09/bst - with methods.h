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
    } 

	// add item to BST
    void insert(const T & t) throw (const char * );
   
   //erase an item in the BST at an iterator
   void erase(BST <T> :: iterator & it);
   
    
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

/********************************************************************
 * CLASS : ITERATOR : This will define an iterator to traverse a list
 ********************************************************************/
template <class T>
class BST <T> :: iterator
{
public:
	//********** CONSTRUCTORS *********//
	// default constructor
	BST <T> :: iterator(BNode * p = NULL)      { pNode.push(p);     }

	// non-default constructor
	BST <T> ::iterator(stack <BNode*> & s)    { pNode = s;         }

	// copy constructor
	BST <T> :: iterator(const iterator & rhs) { pNode = rhs.pNode; }

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
		return rhs.pNode.top() == pNode.top();
	}

	// is not equal operator
	bool operator != (const iterator & rhs)
	{
		// only compare the leaf of nodes
		return rhs.pNode.top() != node.top();
	}

	// de-reference operator
	T & operator * ()
	{
		return pNOde.top()->data;
	}

	// increment 
	iterator & operator ++ ();
	iterator operator ++ (int postfix)
	{
		iterator <T> itReturn = *this;
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

/**************************************************
* BST ITERATOR :: INCREMENT PREFIX
* advance by one
*************************************************/
template <class T>
iterator <T> & iterator <T> :: operator ++ ()
{
	// do nothing if we have nothing
	if (nodes.top() == NULL)
		return *this;

	// if there is a right node, take it
	if (nodes.top()->pRight != NULL)
	{
		nodes.push(nodes.top()->pRight);

		// there might be more left-most children
		while (nodes.top()->pLeft)
			nodes.push(nodes.top()->pLeft);
		return *this;
	}

	// there are no right children, the left are done
	assert(nodes.top()->pRight == NULL);
	BinaryNode <T> * pSave = nodes.top();
	nodes.pop();

	// if the parent is the NULL, we are done!
	if (NULL == nodes.top())
		return *this;

	// if we are the left-child, got to the parent.
	if (pSave == nodes.top()->pLeft)
		return *this;

	// we are the right-child, go up as long as we are the right child!
	while (nodes.top() != NULL && pSave == nodes.top()->pRight)
	{
		pSave = nodes.top();
		nodes.pop();
	}

	return *this;
}

//} // namespace custom

#endif // BST_H
