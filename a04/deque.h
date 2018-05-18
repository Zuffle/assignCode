//
//  deque.h
//  a04
//
//  Created by Justin Parry on 5/16/18.
//  Copyright © 2018 jEnoch. All rights reserved.
//

#ifndef DEQUE_H
#define DEQUE_H

namespace custom
{
   template <class T>
   class deque
   {
   public:
      /***************************
       * CONSTRUCTORS
       ***************************/
      deque() : iFront(0), iBack(0), numCap(0), data(NULL) {}
      deque(int startCap) throw (const char *);
      deque(const deque <T> & rhs) throw (const char *);
      ~deque() { delete [] data; };
      deque & operator = (const deque & rhs) throw (const char *);
      
      /***************************
      * STANDARD INTERFACES
      ***************************/
      int size() const
      {
         return (iBack - iFront) + 1;
      }
      
      bool empty()
      {
         return (size() == 0);
      }
      
      void clear()
      {
         iFront = 0;
         iBack = -1;
      }
      
      /***************************
       * DEQUE INTERFACES
       ***************************/
      void push_front(const T & t)  throw (const char *);
      void push_back(const T & t)  throw (const char *);
      void pop_front();
      void pop_back();
      T & front()  throw (const char *)
      {
         if (empty())
            throw "ERROR: attempting to access an item in an empty deque";
         else
            return data[iFrontNormalize()];
      }
      
      T & back()  throw (const char *)
      {
         if (empty())
            throw "ERROR: attempting to access an item in an empty deque";
         else
            return data[iBackNormalize()];
      }
   
      T & front() const throw (const char *)
      {
         if (empty())
            throw "ERROR: attempting to access an item in an empty deque";
         else
            return data[iFrontNormalize()];
      }
      
      T & back() const throw (const char *)
      {
         if (empty())
            throw "ERROR: attempting to access an item in an empty deque";
         else
            return data[iBackNormalize()];
      }
      
   private:
      T * data;
      int iFront;
      int iBack;
      int numCap;
      
      /***************************
       * MORE INTERFACES
       ***************************/
      void resize(int newCap) throw (const char *);
      int cap() const   { return numCap; }      // returns the capacity of the queue
      int iFrontNormalize() { return iNormalize(iFront); }
      int iBackNormalize() { return iNormalize(iBack); }
      int iNormalize(int index);
   };
   /***************************
    * NON DEFAULT CONSTRUCTOR
    ***************************/
   template <class T>
   deque <T> :: deque(int startCap) throw (const char *)
   {
      if (startCap == 0)
      {
         numCap = 0;
         iFront = 0;
         iBack = -1;
         data = NULL;
         return;
      }
      
      try
      {
         data = new T[startCap];
      }
      
      catch (std::bad_alloc)
      {
         throw "ERROR: unable to allocate a new buffer for deque";
      }
      
      iFront = 0;
      iBack = -1;
      numCap = startCap;
   } //non-d constr
   
   /***************************
    * COPY CONSTRUCTOR
    ***************************/
   template <class T>
   deque <T> :: deque(const deque & rhs) throw (const char *)
   {
      if (rhs.size() == 0)
      {
         numCap = iFront = 0;
         iBack = -1;
         data = NULL;
         return;
      }
      
      // try to allocate data using try to throw if there are memory problems
      try
      {
         data = new T[rhs.size()];
      }
      
      catch (std::bad_alloc)
      {
         throw "ERROR: unable to allocate a new buffer for deque";
      }
      
      iFront = rhs.iFront;
      iBack = rhs.iBack;
      numCap = rhs.numCap;
      for (int i = 0; i < rhs.size(); i++)
      {
         data[i] = rhs.data[i];
      }
      
   } // copy constr
   
   /************************************************
    * ASSIGNMENT OPERATOR
    * makes a copy of the deque in the rhs but only
    * copies the necessary capacity to contain the
    * same number of elements
    ************************************************/
   template <class T>
   deque <T> & deque <T> :: operator = (const deque <T> & rhs) throw (const char *)
   {
      clear();
      
      if (cap() < rhs.size())
      {
         resize(rhs.size());
      }
      
      for (int i = rhs.front(); i <= rhs.back(); i++)
      {
         this -> push_back(rhs.data[iFrontNormalize()]);
      }
   } //assignment op
   
   /*******************************************
    * NORMALIZE
    * returns the index wihtin the bounds of the
    * data array
    *******************************************/
   template <class T>
   int deque <T> :: iNormalize(int index)
   {
      if (index < 0)
      {
         return (cap() + ((index % cap())));
      }
      else
      {
         return (index % cap());
      }
   } //normalize

}


#endif /* DEQUE_H */
