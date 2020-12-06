// Jesse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <stack>

using namespace std;
void baking(vector<int>& cookies)
{
	
}

int main()
{
	int n, k;
	cin >> n;
	cin >> k;
	priority_queue<int,vector<int>,std::greater<int>> cookies;
	for (size_t i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		cookies.push(temp);
	}
	if (cookies.top() >= k)
	{
		cout << "Already all cookies are sweeter than " << k << endl;
	}
	else{
		int times = 0;
		while (!cookies.empty()&& cookies.top()<k)
		{
			int c1 = cookies.top();
			cookies.pop();
			if (cookies.empty())
			{
				cout << -1 << endl;
				return 0;
			}
			int c2 = cookies.top();
			cookies.pop();
			int new_coookie = (c1 + (2 * c2));
			cookies.push(new_coookie);
			times++;
		}
		cout << times << endl;
	}

}

