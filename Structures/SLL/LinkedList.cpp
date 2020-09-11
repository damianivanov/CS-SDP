#include <iostream>;
#include "LinkedList.h";
using namespace std;

int main()
{
	LinkedList<int> LL =  LinkedList<int>();
	LL.add_Element(2);
	LL.add_Element(3);
	LL.add_Element(4);
	LL.add_Element(5);
	LL.add_Element(6);
	LL.add_Element(7);
	LL.Print();
}