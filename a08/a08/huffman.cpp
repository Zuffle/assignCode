/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
//#include "vector.h"        // for VECTOR container
#include "pair.h"          // for PAIR container
#include "huffman.h"       // for HUFFMAN() prototype
#include "list.h"

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using namespace custom;

//****** Typedef ******//
typedef list < BNode < custom::pair < string, float> > * > listBNPP;

//****** Prototypes ******//
bool isLessThan(BNode <custom::pair <string, float> > * newNode, BNode <custom::pair <string, float> > * iteratorNode);
void sortList(list < BNode < custom::pair < string, float> > * > & unsortedList);
void combineFirstTwo(listBNPP & bNodeList);
void insertSort(listBNPP & bNodeList, BNode <custom::pair<string, float> > * newBNode);
BNode<custom::pair < string, float > > combineTwoNodes(listBNPP & BnodeList);
void displayList(listBNPP & bNodeList);
void displayTree(const BNode <custom::pair <string, float> > * pHead);

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman
 *  generation code
 *******************************************/
void huffman(const string & fileName)
{
    listBNPP bNodeList;
    
    ////////////////////////////////////////////////////////////
    
    custom::pair <string, float> readData;
    
    ifstream fin;
    fin.open(fileName.c_str());
    
    while (fin >> readData.first >> readData.second)
    {
        if (bNodeList.size() == 0)
        {
            BNode <custom::pair <string, float> > * newBNode = new BNode<custom::pair <string, float> > (readData);
            bNodeList.push_back(newBNode);
        }
        else
        {
            BNode <custom::pair <string, float> > * newBNode = new BNode<custom::pair <string, float> > (readData);
            insertSort(bNodeList, newBNode);
        }
    }

    ////////////////////////////////////////////////////////////
    
    while (bNodeList.size() > 1)
    {
        combineFirstTwo(bNodeList);
    }
    
    ////////////////////////////////////////////////////////////
    
    BNode <custom::pair <string, float> > * pHead = bNodeList.front();
    
    displayTree(pHead);
    
   return;
}

/*******************************************
 * IsLessThan()
 *  This will check to see if one pair is
 *  less than another
 *******************************************/
bool isLessThan(BNode <custom::pair <string, float> > * newNode, BNode <custom::pair <string, float> > * iteratorNode)
{
    return (newNode->data.second < iteratorNode->data.second);
}

/*******************************************
 * CombineFirstTwo()
 *  This will combine the first two nodes and
 *  place it into the correct place in the
 *  list
 *******************************************/
void combineFirstTwo(listBNPP & bNodeList)
{
    BNode <custom::pair <string, float> > * tempBNode = new BNode < custom::pair <string, float> >;
   
    listBNPP :: iterator it = bNodeList.begin();
    
    tempBNode->data.first = " ";
    tempBNode->data.second = (*it)->data.second;
    tempBNode->pLeft = *it;
    bNodeList.erase(it);
    it = bNodeList.begin();
    
    tempBNode->data.second += (*it)->data.second;
    tempBNode->pRight = *it;
    bNodeList.erase(it);
    it = bNodeList.begin();
    
    if (!bNodeList.empty())
        insertSort(bNodeList, tempBNode);
    else
        bNodeList.push_back(tempBNode);
}

/*******************************************
 * InsertSort()
 *  This will sort the list as we insert
 *******************************************/
void insertSort(listBNPP & bNodeList, BNode <custom::pair<string, float> > * newBNode)
{
    for (listBNPP :: iterator it = bNodeList.begin(); it != bNodeList.end(); it++)
    {
        listBNPP :: iterator tempIt = it;
        tempIt++;
        
        if (isLessThan(newBNode, *it))
        {
            bNodeList.insert(it, newBNode);
            break;
        }
        else if (tempIt == bNodeList.end())
        {
            bNodeList.push_back(newBNode);
            break;
        }
    }
}

/*******************************************
 * DisplayList()
 *  This will display a list
 *******************************************/
void displayList(listBNPP & bNodeList)
{
    for (listBNPP :: iterator yes = bNodeList.begin(); yes != bNodeList.end(); yes++)
    {
        cout << (*yes)->data << endl;
    }
}

/*******************************************
 * DisplayTree()
 *  This will display a tree in order
 *******************************************/
void displayTree(const BNode <custom::pair <string, float> > * pHead)
{
    if (pHead == NULL)
        return;
    
//    cout << "Beginning" << endl;
    displayTree(pHead->pLeft);
    cout << pHead->data.first << " = " << pHead->data.second << endl;
    displayTree(pHead->pRight);
}



