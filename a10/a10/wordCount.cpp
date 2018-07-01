/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    Taylor Williams
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
//void readFile(custom::map <string, Count> & counts, const string & fileName);

void displayMap(custom::map <string, int> words);

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
    string filename;
    cout << "What is the filename to be counted? ";
    cin >> filename;
    
    ifstream fin;
    fin.open(filename.c_str());
    if (fin.fail())
    {
        cout << "ERROR: Unable to read file!";
    }

    custom::map <string, int> words;
    string word1;
    string word2;
    
    while (fin >> word1)
    {
//        for (int i = 0; i < word1.size(); i++)
//        {
//            if (isupper(word1[i]))
//            {
//                word1[i] = tolower(word1[i]);
//            }
//        }
        
        unsigned long size = word1.size();
        
        for (int i = 0; i < size; i++)
        {
            if (ispunct(word1[i]) && word1[i] != '-')
            {
                word1.erase(i, 1);
                i--;
            }
        }
        
        pair <string, int> individualPair;
        individualPair.first = word1;
        
        custom::map <string, int> :: iterator it = words.find(individualPair.first);
        
        if (it != words.end())
        {
            (*it).second += 1;
        }
        else
        {
            individualPair.second = 1;
            words.insert(individualPair.first, individualPair.second);
        }
    }
    
    string input;
    
    cout << "What word whose frequency is to be found. Type ! when done\n";
    cout << "> ";
    cin >> input;
    
    while (input != "!")
    {
        cout << "\t" << input << " : " << words[input] << endl;
        
        cout << "> ";
        cin >> input;
    }
    
}

void displayMap(custom::map <string, int> words)
{
    cout << '{';
    
    typename custom::map < string, int > :: iterator it;
    for (it = words.begin(); it != words.end(); ++it)
        cout << "  " << (*it).second << " - " << (*it).first << endl;
    
    cout << "  }";
}
