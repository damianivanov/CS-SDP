// Knights.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>

using namespace std;

list<int>::const_iterator next(list<int>::const_iterator it,const list<int> &ls) {
	if (it == --ls.end())
		return ls.begin();

	return ++it;
}

list<int>::const_iterator next(list<int>::const_iterator it, const list<int>& ls,int n) {
	while (n>0)
	{
		it = next(it,ls);
		--n;
	}
	return it;
}
list<int>::const_iterator previous(list<int>::const_iterator it, const list<int>& ls) {
	if (it == ls.begin())
		return --ls.end();

	return --it;
}

int winner(list<int> knights)
{
	size_t n = knights.size();
	n = (((n % 2) * 4 + 8) / 2) % n;
	list<int>::const_iterator it = next(knights.begin(), knights, n);
	int k = *it;

	while (knights.size() > 1)
	{
		it = next(it, knights, k);
		k = *it;
		it = previous(knights.erase(it),knights);
	}

	return *knights.begin();
}

int main()
{
	int n;
	cin >> n;
	list<int> knights;
	for (size_t i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		knights.push_back(x);
	}
	cout << winner(knights);

}


