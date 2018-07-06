###############################################################
# Program:
#     Assignment 09, Binary Search Tree
#     Brother Kirby, CS235
# Author:
#     Taylor Williams
# Summary:
#     Defines a Binary Search Tree with its iterator and Binary
#	Node
# Time:
#     Taylor: 4 Hrs.
#     Justin: 6 hours
#     Lu: 6 Hrs.
#     Paired Programming: 2 Hrs.
# Most Difficult Part:
#     Taylor: Probably the erase function. There were just a
#	lot of conditions that we needed to check for.
#     Justin: I think it was hard knowing when it was best to
#	use the iterator to traverse the tree and when it wasn't
#     Lu: The Iterator was very hard to figure out.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment09.o
	g++ -o a.out assignment09.o -g
	tar -cf assignment09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment09.o     : the driver program
##############################################################
assignment09.o: bnode.h bst.h assignment09.cpp
	g++ -c assignment09.cpp -g

