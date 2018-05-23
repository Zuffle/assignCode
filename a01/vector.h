/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of an vector: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       vector            : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{
   
   /************************************************
    * VECTOR
    * A class that holds stuff
    ***********************************************/
   template <class T>
   class vector
   {
   public:
      // constructors and destructors'
      vector()                         { numCapacity = numElements = 0;
         data = NULL;
      }
      vector(int num)                  throw (const char *);
      vector(const vector & rhs)        throw (const char *);
      ~vector()                         { delete [] data;   }
      vector & operator = (const vector & rhs) throw (const char *);
      
      // standard container interfaces
      // vector treats size and max_size the same
      int  size()     const { return numElements;                 }
      int  capacity() const { return numCapacity;                 }
      bool empty()    const {
         if (numElements == 0)
            return true;
         else
            return false;
      }
      
      void push_back(const T &element) throw (const char *); // const by ref so that it is more efficeitn and won't change the original value
      
      // vector-specific interfaces
      // what would happen if I passed -1 or something greater than numElements?
      T & operator [] (int index)       throw (const char *)
      {
         return data[index];
      }
      
      const T & operator [] (int index) const throw (const char *)
      {   
         return data[index];
      }
      
      // the various iterator interfaces
      class iterator;
      iterator begin()      { return iterator (data); }
      iterator rbegin()     { return iterator (data + size()); }
      iterator end()        { return iterator (data + (size())); }
      iterator rend()       { return iterator (&data[-1]);}
      void clear();
      
      // a debug utility to display the vector
      // this gets compiled to nothing if NDEBUG is defined
      void display() const;
      
   private:
      T * data;              // dynamically allocated vector of T
      int numCapacity;
      int numElements;               // both the capacity and the number of elements
      void resize(int capNew);
   };
   
   /**************************************************
    * vector ITERATOR
    * An iterator through vector
    *************************************************/
      template <class T>
      class vector <T> :: iterator
      {
      public:
         // constructors, destructors, and assignment operator
         iterator()      : p(NULL)      {              }
         iterator(T * p) : p(p)         {              }
         iterator(const iterator & rhs) { *this = rhs; }
         iterator & operator = (const iterator & rhs)
         {
            this->p = rhs.p;
            return *this;
         }
         
         // equals, not equals operator
         bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
         bool operator == (const iterator & rhs) const { return rhs.p == this->p; }
         
         // dereference operator
         T & operator * ()       { return *p; }
         const T & operator * () const { return *p; }
         
         // prefix increment
         iterator & operator ++ ()
         {
            p++;
            return *this;
         }
         
         // postfix increment
         iterator operator ++ (int postfix)
         {
            iterator tmp(*this);
            p++;
            return tmp;
         }
         
      private:
         T * p;
      };
   
   /********************************************
    * vector :: END
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
//   template <class T>
//   typename vector <T> :: iterator vector <T> :: end ()
//   {
//      return iterator (data + size());
//   }
   
   /*******************************************
    * vector :: Clear
    *******************************************/
   template <class T>
   void vector <T> :: clear()
   {
      numElements = 0;
   }
   
   /*******************************************
    * vector :: Resize
    *******************************************/
   template <class T>
   void vector <T> :: resize(int capNew)
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
      data = arrayNew;
      numCapacity = capNew;
   }
   
   
   /*******************************************
    * vector :: Assignment
    *******************************************/
   template <class T>
   vector <T> & vector <T> :: operator = (const vector <T> & rhs)
   throw (const char *)
   {
      if (rhs.size() > capacity())
      {
         resize(rhs.size());
      }
      
      numElements = rhs.size();
      
      assert(numCapacity >= rhs.numElements);
      for (int i = 0; i < numElements; i++)
      {
         data[i] = rhs.data[i];
      }
      
      return *this;
   }
   
   
   /*******************************************
    * vector :: COPY CONSTRUCTOR
    *******************************************/
   template <class T>
   vector <T> :: vector(const vector <T> & rhs) throw (const char *)
   {
      assert(rhs.numCapacity >= 0);
      
      // do nothing if there is nothing to do
      if (rhs.numElements == 0)
      {
         numElements = 0;
         numCapacity = 0;
         data = NULL;
         return;
      }
      
      // attempt to allocate
      try
      {
         data = new T[rhs.numCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
      
      // copy over the capacity and size
      numCapacity = rhs.numCapacity;
      numElements = rhs.numElements;
      
      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numCapacity; i++)
      {
         data[i] = rhs.data[i];
      }
   }
   
   /**********************************************
    * vector : NON-DEFAULT CONSTRUCTOR
    * Preallocate the vector to "capacity"
    **********************************************/
   template <class T>
   vector <T> :: vector(int num) throw (const char *)
   {
      assert(num >= 0);
      
      // do nothing if there is nothing to do.
      
      if (num == 0)
      {
         this->numElements = 0;
         this->numCapacity = 0;
         this->data = NULL;
         return;
      }
      
      // attempt to allocate
      try
      {
         data = new T[num];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
      
      
      // copy over the stuff
      this->numCapacity = num;
      this->numElements = num;
      
      // initialize vector with values
      for (int i = 0; i < numCapacity; i++)
      {
         data[i] = 0;
      }
      
   }
   /********************************************
    * vector : PUSH_BACK
    * A function to put items into the vector and resize if needed
    *******************************************/
   template <class T>
   void vector <T> :: push_back(const T &element) throw (const char *)
   {
      //TODO: push_back function. check if elements are greater than capacity if so make a new array w/double size and copy new contents over
      if (size() >= capacity())
      {
         resize((capacity() == 0 ? capacity() + 1 : capacity() * 2));
      }
      
      data[numElements++] = element;
   }
   
   /********************************************
    * vector : DISPLAY
    * A debug utility to display the contents of the vector
    *******************************************/
   //template <class T>
   //void vector <T> :: display() const
   //{
   //#ifndef NDEBUG
   //   std::cerr << "vector<T>::display()\n";
   //   std::cerr << "\tnum = " << num << "\n";
   //   for (int i = 0; i < num; i++)
   //      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
   //#endif // NDEBUG
   //}
   
}; // namespace custom

#endif // vector_H

