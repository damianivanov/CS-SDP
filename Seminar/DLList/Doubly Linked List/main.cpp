// Doubly Linked List.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "DLList.h"
#include <iostream>

void print(DLList<int> &l)
{
    for (auto it=l.begin();it!=l.end();++it)
    {
        std::cout<<*it<<std::endl;
    }
}

int main()
{
    DLList<int> a;
    a.push_back(4);
    a.push_back(5);
    a.push_back(6);
    a.push_back(7);
    DLList<int> b(a), c;
    c = a;
    b.push_back(8);
    c.push_back(8);
    c.push_back(9);
    print(c);
    return 0;
}

