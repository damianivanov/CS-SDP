// PStack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PStack.cpp"

void printstack(PStack<int> s)
{
    while (!s.empty()) {
        std::cout << s.top() << std::endl;
        s = s.pop();
    }
}

int main()
{
    PStack<int> s = PStack<int>().push(1).push(2).push(3);
    printstack(s);
    
}
