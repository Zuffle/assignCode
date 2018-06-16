/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "wholeNumber.h"
using namespace std;

ostream & operator << (ostream & out, WholeNumber & rhs)
{
   list <int> :: reverse_iterator it;
   it = rhs.wholeNumber.rbegin();
    //cerr << ".1";// << rhs.wholeNumber.front();
    out << *it;
    //cerr << ".2";
    while (it != rhs.wholeNumber.rend())
    {
       //cerr << ".3" << "\t" << *it;
       if (it == rhs.wholeNumber.rend())
//          cerr << "it = rend so it should stop";
        out << *it;
        ++it;
      //  cerr << ".4" << "\t" << *it;
    }
    return out;
}
/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;

   WholeNumber previous(0);
   WholeNumber current(1);
   WholeNumber sum(0);
    

    for (int i = 1; i <= number; i++)
    {
////       cerr << "LOOPING!";
        if (i == 1)
            cout << "\t" << 1 << endl;
        else
        {
//           cerr << endl;//"1";
//           //cerr << "what is previous + current?" << (previous + current) << endl;
            sum = previous + current;
////            cerr << "sum is";
////            cerr << sum;
//            //cerr << "before 2:" << sum.wholeNumber.front() <<" " << sum.wholeNumber.back();
////            cerr << "2";
////            cout << "\t" << sum << endl;
////            cerr << "3";
            previous = current;
////            cerr << "4";
            current  = sum;
////            cerr << "5" << endl;
            //current += previous;
            cout << "\t" << current << endl;
//            sum = current;
//            previous = current - previous;
        }
    }

   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;
   
   previous = 0;
   current  = 1;
   sum = 0;
   
    for (int j = 1; j <= number; j++)
    {

       if (j == 1)
        {
            if (number == 1)
                cout << "\t" << 1 << endl;
        }
        else
        {
            sum = previous + current;
            
            if (j == number)
                cout << "\t" << sum << endl;
            
            previous = current;
            current  = sum;
        }
    }
}

