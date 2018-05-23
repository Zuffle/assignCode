//
//  set.h
//  a05
//
//  Created by Justin Parry on 5/22/18.
//  Copyright © 2018 jEnoch. All rights reserved.
//

#ifndef set_h
#define set_h
namespace custom
{
   template <class T>
   class set
   {
   public:
      /***************************
       * CONSTRUCTORS
       ***************************/
      set() : numElem(0), numCap(0), data(NULL) {}
      set(int newCap) throw (const char *);
      set(const set & rhs) throw (const char *);
      ~set()
      {
         delete [] data;
      }
      set & operator = (const set & rhs) throw (const char *);
      
      /***************************
       * STANDARD INTERFACES
       ***************************/
      int size() const { return numElem; }
      int cap() const { return numCap; }
      bool empty () { return (size() == 0); }
      void clear() { numElem = 0; }
   
   private:
      T * data;
      int numElem;
      int numCap;
      void resize(int newCap) throw (const char *);
      
   }; // set class
   
   /***************************
    * NON DEFAULT CONSTRUCTOR
    ***************************/
   template <class T>
   set <T> :: set(int newCap) throw (const char *)
   {
      if (newCap == 0)
      {
         numElem = 0;
         numCap = 0;
         data = NULL;
         return;
      }
      
      try
      {
         data = new T[newCap];
      }
      
      catch (std::bad_alloc)
      {
         throw "ERROR: unable to allocate new buffer for set";
      }
      
      numElem = 0;
      numCap = newCap;
   } // non default constr
   
   /***************************
    * COPY CONSTRUCTOR
    ***************************/
   template <class T>
   set <T> :: set(const set & rhs) throw (const char *)
   {
      if (rhs.size() == 0)
      {
         numCap = numElem = 0;
         data = NULL;
         return;
      }
      
      try
      {
         data = new T[rhs.size()];
      }
      
      catch (std:: bad_alloc)
      {
         throw "ERROR: unable to allocate a new buffer for set";
      }
      
      // copy over variables
      numElem = rhs.numElem;
      numCap = rhs.numCap;
      for (int i = 0; i < rhs.numElem; i++)
      {
         data[i] = rhs.data[i];
      }
      
   } // copy constr
   
   /************************************************
    * ASSIGNMENT OPERATOR
    ************************************************/
   template <class T>
   set <T> & set <T> :: operator = (const set <T> & rhs) throw (const char *)
   {
      
      if (rhs.size() == 0)
      {
         numCap = numElem = 0;
         data = NULL;
         return *this;
      }
      
      try
      {
         data = new T[rhs.size()];
      }
      
      catch (std:: bad_alloc)
      {
         throw "ERROR: unable to allocate a new buffer for set";
      }
      
      // copy over variables
      numElem = rhs.numElem;
      numCap = rhs.numCap;
      for (int i = 0; i < rhs.size(); i++)
      {
         data[i] = rhs.data[i];
      }
      
      return *this;
   } // assign op
   
   /*******************************************
    * RESIZE
    *******************************************/
   template <class T>
   void  set <T> :: resize(int capNew) throw (const char *)
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
         for (int i = 0; i < numElem; i++)
            arrayNew[i] = data[i];
      else
      {
         for (int i = 0; i < numElem; i++)
            arrayNew[i] = '0';
      }
      
      delete [] data;
      data = arrayNew;
      numCap = capNew;
   }
   
} //namespace custom

#endif /* set_h */
