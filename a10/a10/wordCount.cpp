/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
#include <iostream>
#include <fstream>
using namespace std;
void readFile(custom::map <string, int> & counts, const string & fileName);

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{

}

/*****************************************************
 * READ FILE
 * Reads file from a given string
 *****************************************************/
void readFile(custom::map <string, int> & counts, const string & fileName)
{
   ifstream fin(fileName.c_str());
   
   if (fin.fail())
   {
      cout << "ERROR: Could not read file\n";
      return;
   }
   
   string word;
   while (fin >> word)
   {
      // TODO: Needed to write the insert method first
      //counts.insert(
   }
   
}
