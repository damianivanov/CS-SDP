// STLQueue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Queue.h"

int main()
{
	Queue<int> queue;
	queue.push(3);
	queue.push(4);
	queue.push(5);

	while (!queue.empty())
	{
		std::cout << queue.top() << std::endl;
		queue.pop();
	}
}

