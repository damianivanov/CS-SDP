// StreeetParade.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <stack>

using namespace std;


int main()
{
	int n = 0;
	cin >> n;
	queue<int> cars;
	stack<int> street;
	for (size_t i = 0; i < n; i++)
	{
		int number = 0;
		cin >> number;
		cars.push(number);
	}

	int next = 1;
	while (!cars.empty())
	{
		int x = cars.front();
		cars.pop();
		if (x == next) next++;
		else {
			if (!street.empty() && street.top() == next)
			{
				street.pop();
			}
			else if (cars.size()!=0 && (street.empty() || x<street.top()))
			{
				street.push(x);
			}
			else {
				cout << "no" << endl;
				return 0;
			}
		}
	}
	cout << "yes" << endl;
}