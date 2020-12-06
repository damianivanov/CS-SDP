// SinglyLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "SLList.h"

int main()
{
	SLList<int> list;
	list.push_back(5);
	list.push_back(6);
	list.push_back(7);
	list.push_back(8);
	list.push_back(9);
	list.print();
	SLList<int> newlist(list);
	std::cout << "------------------\n";
	newlist.print();
}


