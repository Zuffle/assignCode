//
//  stack.h
//  Week 2
//
//  Created by Taylor Williams on 4/30/18.
//  Copyright © 2018 Taylor Williams. All rights reserved.
//

#ifndef stack_h
#define stack_h

namespace custom
{

template <class T>
class stack
{
public:
    /*** CONSTRUCTORS ***/
    stack()  : numElements(0), numCapacity(0), data(NULL) {}
    stack(int capacity)      throw (const char *);
    stack(const stack & rhs) throw (const char *);
    ~stack() { if (numCapacity) delete [] data; }
    
    /*** OPERATORS ***/
    stack <T> & operator = (const stack <T> & rhs) throw (const char *);
    
    /*** FUNCTIONS ***/
    int size() const      { return numElements;   }  // This will return the amount of elements in the stack
    int capacity() const  { return numCapacity;   }  // This will return the capacity of the stack
    bool empty()          { return (size() == 0); }  // This will check to see if the stack is empty
    void clear()          { numElements = 0;      }  // This will clear the stack
    T top ()                                         // Returns the value at the top of the stack
    {
        if (!empty())
            return data[numElements - 1];
        else
            throw ("ERROR: Unable to reference the element from an empty Stack");
    }
    void push(const T & t) throw (const char *);
    void pop() throw (const char *);
    
private:
    T * data;                    // Dynamically allocated array of T
    int numElements;             // How many items are CURRENTLY in the container?
    int numCapacity;             // How many items CAN I put in the container?
    void resize(int newCap);     // This will reallocate the stack to twice the size
};

/************************************************
*          NON-DEFAULT CONSTRUCTOR
* If the user sends over information about size
************************************************/
template <class T>
stack <T> :: stack (int cap) throw (const char *)
{
        if (cap == 0)          // Do nothing if there is nothing to do
        {
            numCapacity = 0;
            numElements = 0;
            data = NULL;
            return;
        }
    
        try                      // Attempt to allocate
        {
            data = new T[cap];
        }
        catch (std::bad_alloc)   // Otherwise, give an ERROR message
        {
            throw "ERROR: Unable to allocate buffer";
        }
    
        numCapacity = cap;       // Set capacity to passed in capacity
        numElements = 0;         // There are no items
    
        for (int i = 0; i < cap; i++)     // Initialize the empty slots with a defealt
        {
            data[i] = T();
        };
        
}
    
/*************************************************
 *               COPY CONSTRUCTOR
 * Create a new Stack exactly the same as another
 ************************************************/
 template <class T>
 stack <T> :: stack(const stack <T> & rhs) throw (const char *)
 {
     if (rhs.numCapacity == 0)      // Do nothing if there is nothing to do
     {
        numCapacity = 0;
        numElements = 0;
        data = NULL;
        return;
     }
     
     try                    // Attempt to allocate
     {
         data = new T[rhs.numCapacity];
     }
     catch (std::bad_alloc)
     {
         throw "ERROR: Unable to allocate buffer";
     }
     
     numCapacity = rhs.numCapacity;      // Copy over the caoacity and top value
     numElements = rhs.numElements;
        
     for (int i = 0; i < numElements; i++)
            data[i] = rhs.data[i];
         
     for (int i = numElements; i < numCapacity; i++)
            data[i] = T();
}

/***********************************
 *         =  OPERATOR
 * Copy Stack using = operator
 ***********************************/
 template <class T>
 stack <T> & stack <T> :: operator = (const stack <T> & rhs) throw (const char *)
 {
     // If the Stack is empty
     if (rhs.numCapacity == 0)
     {
         numCapacity = 0;
         numElements = 0;
         data = NULL;
         return *this;
     }
        
     // If the one you are copying is larger
     if (rhs.numCapacity > this->numCapacity)
     {
         delete [] data;
         data = NULL;
            
         try
         {
             data = new T[rhs.numCapacity];
         }
         catch (std::bad_alloc)
         {
             throw "ERROR: Uable to allocate buffer";
         }
            
         numCapacity = rhs.numCapacity;
         numElements = rhs.numElements;
            
         for (int i = 0; i < numCapacity; i++)
                data[i] = rhs.data[i];
     }
        
     // If your vector is larger than the other
     if (rhs.numCapacity <= this->numCapacity)
     {
         numElements = rhs.numElements;
            
         for (int i = 0; i < numElements; i++)
             data[i] = rhs.data[i];
                
         for (int i = numElements; i < numCapacity; i++)
                data[i] = T();
     }
        
     // Return the Stack
     return *this;
 }
    
/**********************************
 *          PUSH()
 * Push an item onto the stack
 *********************************/
 template <class T>
 void stack <T> :: push(const T & t) throw (const char *)
{
    if (size() == capacity())
    {
        if (capacity() == 0)
            resize(capacity() + 1);
        else
            resize(capacity() * 2);
    }

    data[numElements++] = t;
}
    
/****************************
 *         POP()
 * Decrease my top by one
 ***************************/
 template <class T>
 void stack <T> :: pop() throw (const char *)
 {
     // Decrease number of elements in the Stack
     if ( !empty() )
     {
         numElements--;
     }
 }
    
/*****************************************************
 *                   RESIZE()
 *  This will reallocate the stack to twice the size
 ****************************************************/
template <class T>
void stack <T> :: resize(int newCap)
{
    T * temp;
    temp = new T[newCap];                   // Create a temporary placeholder
    
    for (int i = 0; i < numElements; i++)  // Copy over the elements
    {
        temp[i] = data[i];
    }
    
    delete [] data;                // Delete original pointer
    
    data = temp;                   // Point the original at the newly created stack
    numCapacity = newCap;          // Reassign the capacity to the new capacity
}

};

#endif /* stack_h */
