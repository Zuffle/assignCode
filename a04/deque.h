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
      deque() : iFront(0), iBack(-1), numCap(0), data(NULL) {}
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
      
      bool empty() const
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
      void push_front(const T & t) throw (const char *);
      void push_back(const T & t) throw (const char *);
      void pop_front() throw (const char *);
      void pop_back() throw (const char *);
      T & front() throw (const char *)
      {
         if (empty())
            throw "ERROR: attempting to access an item in an empty deque";
         else
            return data[iFrontNormalize()];
      }
      
      T & back() throw (const char *)
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
      int iFrontNormalize() const { return iNormalize(iFront); }
      int iBackNormalize() const { return iNormalize(iBack); }
      int iNormalize(int index);
      int iNormalize(int index) const ;
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
      return *this;
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
   
   /*******************************************
    * NORMALIZE const
    * returns the index wihtin the bounds of the
    * data array
    *******************************************/
   template <class T>
   int deque <T> :: iNormalize(int index) const
   {
      if (index < 0)
      {
         return (cap() + ((index % cap())));
      }
      else
      {
         return (index % cap());
      }
   } //normalize const
   
   /*******************************************
    * PUSH_FRONT
    * adds element to the front of the deque
    *******************************************/
   template <class T>
   void deque <T> :: push_front(const T &t) throw (const char *)
   {
      if (size() == cap())
      {
         resize((numCap == 0) ? numCap + 1 : numCap * 2);
      }
      
      iBack++;
      data[iBackNormalize()] = t;
   }
   
   /*******************************************
    * PUSH_BACK
    * adds element to the back of the deque
    *******************************************/
   template <class T>
   void deque <T> :: push_back(const T &t) throw (const char *)
   {
      if (size() == cap())
      {
         resize((numCap == 0) ? numCap + 1 : numCap * 2);
      }
      
      iBack++;
      data[iFrontNormalize()] = t;
   }
   
   /*******************************************
    * POP_FRONT
    * removes an element from the front of
    * the deque
    *******************************************/
   template <class T>
   void deque <T> :: pop_front() throw (const char *)
   {
      if (empty())
      {
         throw "ERROR: deque is empty";
      }
      
      iFront++;
   }
   
   /*******************************************
    * POP_BACK
    * removes an element from the back of the
    * deque
    *******************************************/
   template <class T>
   void deque <T> :: pop_back() throw (const char *)
   {
      if (empty())
      {
         throw "ERROR: deque is empty";
      }
      
      iBack++;
   }
   
   /*******************************************
    * RESIZE
    * resizes the queue to the indicated value
    *******************************************/
   template <class T>
   void deque <T> :: resize(int newCap) throw (const char *)
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
         for (int i = 0, iData = iFrontNormalize(); i < size(); i++)
         {
            dataNew[i] = data[iData];
            iData = (iData + 1) % numCap;
         }
      
      if (data != NULL)
         delete [] data;
      
      data = dataNew;
      iBack = size() - 1;
      iFront = 0;
      numCap = newCap;
   } // Resize

}


#endif /* DEQUE_H */
