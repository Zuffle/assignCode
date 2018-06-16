//
//  wholeNumber.h
//  Week 7
//
//  Created by Taylor Williams on 6/7/18.
//  Copyright © 2018 Taylor Williams. All rights reserved.
//

#ifndef wholeNumber_h
#define wholeNumber_h

#include "list.h"
#include <iostream>
using namespace std;

class WholeNumber
{
public:
   //friend std::ostream & operator << (std::ostream & out, WholeNumber & rhs);
	WholeNumber(unsigned int number)
	{
      wholeNumber.clear();
		wholeNumber.push_front(number);
	}
	WholeNumber(list <int> wN)
	{
      wholeNumber = wN;
	}
   
	WholeNumber & operator = (WholeNumber & rhs)
	{
      //list wholenumber.clear
      // for loop rhs and push each member to wholenumber
//      cerr << "assign";
//      cerr << rhs.wholeNumber.front();
//      cerr << "assign1";/
		this->wholeNumber = rhs.wholeNumber;
//      cerr << "thisassign";
//      cerr << this->wholeNumber.front();
      return *this;
	}
   
   WholeNumber & operator = (int rhs)
   {
      WholeNumber tmp(rhs);
      this->wholeNumber = tmp.wholeNumber;
      return *this;
   }
   /*WholeNumber & operator +=(WholeNumber & rhs)
   {
      list <int> previous = rhs.wholeNumber;
      list <int> current = this->wholeNumber;
      list <int> sum;
         
      int remainder = 0;
      int bigSum = 0;
      int individualSum = 0;
      
      typename list <int> ::reverse_iterator itCurrent = current.rbegin();
		typename list <int> ::reverse_iterator itPrevious = previous.rbegin();
      
      while(itCurrent != current.rend())
      {
         if (itPrevious != previous.rend())
			{
				bigSum = *itPrevious + *itCurrent + remainder;
				remainder = bigSum / 1000;
				individualSum = bigSum % 1000;

				sum.push_front(individualSum);

				itCurrent++;
				itPrevious++;
			}
			else
			{
				sum.push_front(*itCurrent + remainder);
				itCurrent++;
			}
		}

		WholeNumber wholeSum(sum);
		return wholeSum;
   }*/
   
	WholeNumber & operator +(WholeNumber rhs)
	{
		list <int> current = rhs.wholeNumber;
		list <int> previous = this->wholeNumber;

		int remainder = 0;
		int bigSum = 0;
		int individualSum = 0;

		list <int> sum;

		typename list <int> ::reverse_iterator itCurrent = current.rbegin();
		typename list <int> ::reverse_iterator itPrevious = previous.rbegin();

		while (itCurrent != current.rend())
		{
//         cerr << "inside while";
			if (itPrevious != previous.rend())
			{
//            cerr << "in if";
				bigSum = *itPrevious + *itCurrent + remainder;
				remainder = bigSum / 1000;
				individualSum = bigSum % 1000;

				sum.push_front(individualSum);
//            cerr << "ind sum" << individualSum << "\t";
				itCurrent++;
				itPrevious++;
			}
			else
			{
//            cerr << "in/ else";
				sum.push_front(*itCurrent + remainder);
				itCurrent++;
			}
		}

		WholeNumber * wholeSum = new WholeNumber(sum);
//      std::cerr << "aftersum" << sum.front() << "\t" << wholeSum.wholeNumber.front();
		return *wholeSum;
	}

	list <int> wholeNumber;



};


#endif /* wholeNumber_h */
