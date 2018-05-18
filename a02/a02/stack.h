/*********************************************************
 * Class: Stack
 *
 *
 *********************************************************/
#ifndef STACK_H
#define STACK_H

#include <cassert>
#include <new>      // for bad_alloc catch

namespace custom
{
   /**************************************
    * STACK CLASS
    * Container to hold things in a stack
    * Last in first out
    **************************************/
   template <class T>
   class stack
   {
   public:
      /***************************
       * CONSTRUCTORS
       ***************************/
      stack() : numElements(0), numCap(0), data(NULL) {}
   
      stack(int max) throw (const char *);
      stack(const stack & rhs) throw (const char *);
      ~stack()                     { delete [] data; }
      stack & operator = (const stack & rhs) throw (const char *);
      
      /***************************
       * STANDARD INTERFACES
       ***************************/
      int size() const  { return numElements; }
      int cap() const   { return numCap; }      // returns the capacity of the stack
      bool empty() { if (size())
                        return false;
                     else
                        return true;
                   }
      void clear() { numElements = 0; }
      
      /***************************
       * STACK INTERFACES
       ***************************/
      void push(const T & e) throw (const char *);
      void pop();
      T & top() throw (const char *);
      T & top() const throw (const char *);
      void resize(int capNew) throw (const char *);
      
   private:
      int numElements;
      int numCap;                // number of possible values in stack
      T * data;                  // allocated array of type T
      
   }; // stack class

   /***************************
    * NON DEFAULT CONSTRUCTOR
    ***************************/
   template <class T>
   stack <T> :: stack(int max) throw (const char *)
   {
      
      assert (max >= 0);
      
      if (max <= 0)
      {
         this -> numCap = 0;
         this -> numElements = 0;
         this -> data = NULL;
         return;
      }
      
      // attmept allocation
      try
      {
         data =  new T[max];
      }
      
      catch (std::bad_alloc)
      {
         throw "ERROR: unable to allocate buffer new buffer for Stack.";
      }
      
      numElements = 0;
      numCap = max;
      
   } // non default constr
   
   /***************************
    * COPY CONSTRUCTOR
    ***************************/
   template <class T>
   stack <T> :: stack(const stack & rhs) throw (const char *)
   {
      
      assert(rhs.numCap >= 0);
      
      if (rhs.numElements == 0)
      {
         this -> numElements = 0;
         this -> numCap = 0;
         this -> data = NULL;
         return;
      }
      
      // attempt allocation
      try
      {
         data = new T[rhs.numElements];
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: unable to allocate buffer";
      }
      
      // copy over size
      this -> numElements = rhs.numElements;
      
   } // copy constr
   
   /************************************************
    * PUSH
    * pushes an element on the top of the stack
    ************************************************/
   template <class T>
   void stack <T> :: push(const T & e) throw (const char *)
   {
      
      if (size() == cap())
      {
         if (cap() == 0)
            resize(numCap + 1);
         else
            resize(numCap *2);
      }
      
      data[numElements++] = e;
      
   } // push
   
   /************************************************
    * POP
    * removes the last element in the array
    ************************************************/
   template <class T>
   void stack <T> :: pop()
   {
      
      if (empty())
         ;
      else
         numElements--;
      
   } // pop
   
   /************************************************
    * TOP
    * gives access to the top element on the stack
    ************************************************/
   template <class T>
   T & stack <T> :: top() throw (const char *)
   {
      
      if (empty())
         throw "ERROR: Unable to access null value";
      else
         return data[numElements - 1];
      
   } // top
   
   /************************************************
    * TOP const
    * gives read only access to the top element
    ************************************************/
   template <class T>
   T & stack <T> :: top() const throw (const char *) // const unable to change top value of the stack
   {
      
      if (empty())
         throw "ERROR: Unable to access null value";
      else
         return data[numElements - 1];
      
   } // top const
   
   /************************************************
    * ASSIGNMENT OPERATOR
    * makes a copy of the stack in the rhs but only
    * copies the necessary capacity to contain the
    * same number of elements
    ************************************************/
   template <class T>
   stack <T> & stack <T> :: operator = (const stack <T> & rhs) throw (const char *)
   {
      
      clear();
      
      if (cap() <= rhs.size())
      {
         resize(rhs.size());
      }
      
      for (int i = 0; i < rhs.size() - 1; i++)
      {
         data[i] = rhs.data[i];
      }
      
      numElements = rhs.size();
      
      return *this;
      
   } // overloaded assignment operator
   
   /*******************************************
    * RESIZE
    * resizes the stack to the indicated value
    *******************************************/
   template <class T>
   void stack <T> :: resize(int capNew) throw (const char *)
   {
      
      T * arrayNew;
      
      // attempt to allocate
      try
      {
         arrayNew = new T[capNew];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
      if (data != NULL)
         for (int i = 0; i < numElements; i++)
            arrayNew[i] = data[i];
      else
      {
         for (int i = 0; i < numElements; i++)
            arrayNew[i] = '0';
      }
      
      delete [] data;
      this -> data = arrayNew;
      this -> numCap = capNew;
      
   } // Resize
   
   
} // namespace custom closing brace


#endif /* stack_h */
