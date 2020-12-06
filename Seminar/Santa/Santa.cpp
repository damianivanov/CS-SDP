// Santa.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <queue>
#include <list>

using namespace std;


int main()
{
	int n;
	cin >> n;
	list<queue<int>> carts;

	for (size_t i = 0; i < n; i++)
	{
		int s;
		cin >> s;
		queue<int> q;
		for (size_t i = 0; i < s; i++)
		{
			int tmp;
			cin >> tmp;
			q.push(tmp);
		}
		carts.push_back(q);
	}
}

