/*********************************************************
 *
 *
 *
 ********************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
#include <iostream>
using std::cerr;
using std::endl;

namespace custom
{
   template <class T>
   class queue
   {
   public:
      /***************************
       * CONSTRUCTORS
       ***************************/
      queue() : numPush(0), numPop(0), numCap(0), data(NULL) {}
      
      queue(int max) throw (const char *);
      queue(const queue & rhs) throw (const char *);
      ~queue()                     { delete [] data; }
      queue & operator = (const queue & rhs) throw (const char *);
      
      /***************************
       * STANDARD INTERFACES
       ***************************/
      int size() const  { return numPush - numPop; }
      int cap() const   { return numCap; }      // returns the capacity of the queue
      bool empty() { return (size() == 0); }
      void clear() { numPush = numPop; }
      
      /***************************
       * QUEUE INTERFACES
       ***************************/
      void push(const T & t) throw (const char *);
      void pop();
      T & front()         throw (const char *);
      T & front()   const throw (const char *);
      T & back()          throw (const char *);
      T & back()    const throw (const char *);
      int iTail() const { return (numPush) % numCap; }
//       cerr << "numPush: " << numPush << endl; cerr << "numCap: " << numCap << endl; cerr << " Push-1 % Cap: " << (numPush - 1) % numCap << endl;
      int iHead() const { return numPop % numCap; }
      
   private:
      // these two variables together can keep track of the size and frnt and back of our queue
      int numPush;                                 // keeps track of the num of items pushed
      int numPop;                                  // keeps track of # of items popped off
      int numCap;
      T * data;
      void resize(int newCap) throw (const char *);
   };
   
   /***************************
    * NON DEFAULT CONSTRUCTOR
    ***************************/
   template <class T>
   queue <T> :: queue(int max) throw (const char *)
   {
      
//      assert (max >= 0);
      
      if (max == 0)
      {
         this -> numCap = 0;
         this -> numPush = 0;
         this -> numPop = 0;
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
         throw "ERROR: unable to allocate a new buffer for queue";
      }
      
      numPush = 0;
      numPop = 0;
      numCap = max;
      
//      for (int i = 0; i < numcap; i++)
//      {
//         data[i] = T();
//      }
      
   } // non default constr
   
   /***************************
    * COPY CONSTRUCTOR
    ***************************/
   template <class T>
   queue <T> :: queue(const queue & rhs) throw (const char *)
   {
      if (rhs.size() == 0)
      {
         numCap = numPush = numPop = 0;
         data = NULL;
         return;
      }
      
      // attempt allocation
      try
      {
         data = new T[rhs.size()];
      }
      catch(std::bad_alloc)
      {
         throw "ERROR: unable to allocate a new buffer for queue";
      }
      
      // copy over size
      numPush = rhs.numPush;
      numPop = rhs.numPop;
      numCap = rhs.numCap;
      for (int i = 0; i < rhs.numPush; i++)
      {
         data[i] = rhs.data[i];
      }
   } // copy constr
   
   /************************************************
    * ASSIGNMENT OPERATOR
    * makes a copy of the queue in the rhs but only
    * copies the necessary capacity to contain the
    * same number of elements
    ************************************************/
   template <class T>
   queue <T> & queue <T> :: operator = (const queue <T> & rhs) throw (const char *)
   {
      
      numPush = numPop = 0;
      
      if (cap() <= rhs.size())
      {
         resize(rhs.size());
      }
      
      for (int i = rhs.numPop; i < rhs.numPush; i++)
      {
         this->push(rhs.data[i % rhs.numCap]);
      }
      
      return *this;
      
   } // overloaded assignment operator

   /*******************************************
    * FRONT
    * retrieves the element from the front
    *******************************************/
   template <class T>
   T & queue <T> :: front() throw (const char *)
   {
      if (empty())
         throw "ERROR: attempting to access an item in an empty queue";
      else
         return data[iHead()];
   }
   
   /*******************************************
    * FRONT const
    * retrieves the element from the front
    *******************************************/
   template <class T>
   T & queue <T> :: front() const throw (const char *)
   {
      if (empty())
         throw "ERROR: attempting to access an item in an empty queue";
      else
         return data[iHead()];
   }
   
   /*******************************************
    * BACK
    * retrieves the element from the front
    *******************************************/
   template <class T>
   T & queue <T> :: back() throw (const char *)
   {
      if (empty())
         throw "ERROR: attempting to access an item in an empty queue";
      else
         return data[iTail()];
   }
   
   /*******************************************
    * BACK const
    * retrieves the element from the front
    *******************************************/
   template <class T>
   T & queue <T> :: back() const throw (const char *)
   {
      if (empty())
         throw "ERROR: attempting to access an item in an empty queue";
      else
         return data[iTail()];
   }
   
   /*******************************************
    * PUSH
    * adds elements to the end of the queue
    *******************************************/
   template <class T>
   void queue <T> :: push(const T & t) throw (const char *)
   {
      if (size() == numCap)
      {
         resize((numCap == 0) ? numCap + 1 : numCap * 2);
      }
      
      cerr << "t: " << t << endl;
      data[iTail()] = t;
//      data[(iTail() == 0) ? iTail() : iTail() + 1] = t;
      
      numPush++;
      cerr << "iTai: " << iTail() << endl;
      cerr << "data[tail]: " << data[iTail()] << endl;
   }
   
   /*******************************************
    * POP
    * removes elems from the beginning of queue
    *******************************************/
   template <class T>
   void queue <T> :: pop()
   {
      if (!empty())
         numPop++;
   }
   
   /*******************************************
    * RESIZE
    * resizes the queue to the indicated value
    *******************************************/
   template <class T>
   void queue <T> :: resize(int newCap) throw (const char *)
   {
      
      T * dataNew;
      
//      int cap = numCap;
//
//      if (numCap == 0)
//         cap = 1;
//      else
//         cap *= 2;
      
      // attempt to allocate
      try
      {
         dataNew = new T[newCap];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
      
      if (size() > 0)
         for (int i = 0, j = iHead(); i < size(); i++)
         {
            dataNew[i] = data[j];
            j = (j + 1) % numCap;
         }
      
      if (data != NULL)
         delete [] data;
      
      data = dataNew;
      numPush = size();
      numPop = 0;
      numCap = newCap;
   } // Resize
   
}
#endif /* QUEUE_H */
