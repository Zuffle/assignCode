/***********************************************************************
* Header:
*    INFIX      
* Summary:
*    This will contain just the prototype for the convertInfixToPostfix()
*    function
* Author
*    <your names here>
************************************************************************/

#ifndef INFIX_H
#define INFIX_H

#include <string>

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix();

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly();

std::string convertInfixToPostfix(const std::string & infix);

#endif // INFIX_H

