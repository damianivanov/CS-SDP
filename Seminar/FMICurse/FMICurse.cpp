// FMICurse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<list>
using namespace std;
void extremums(const list<int>& l,list<int>::const_iterator &min_el,list<int>::const_iterator &max_el) 
{
	for (list<int>::const_iterator it=++l.begin(); it != l.end(); it++)
	{
		if (*it > * max_el) max_el = it;
		if (*it < * min_el) min_el = it;
	}
}


void curse(list<int> &l)
{
	list<int>::const_iterator min_el = l.begin();
	list<int>::const_iterator max_el = l.begin();
	extremums(l,min_el, max_el);
	
	int m = *min_el;
	int n = *max_el;

	l.insert(min_el, 2 * m);
	l.insert(min_el, 2 * m + 1);
	
	l.insert(max_el, n/2);
	l.insert(max_el, n/2 + 1);
	
	l.erase(min_el);
	l.erase(max_el);
	
	int prev = *l.begin();
	bool equal = false;

	for (list<int>::const_iterator it =++l.begin();  it != l.end(); it++)
	{
		if (*it == prev) equal = true;
		prev = *it;
	}
	if (!equal) curse(l);

}

int main()
{
	list<int> l;
	int n = 0;
	cin >> n;
	for (size_t i = 0; i < n; i++)
	{
		int tmp = 0;
		cin >> tmp;
		l.push_back(tmp);
	}
	
	curse(l);

	for (list<int>::const_iterator it=l.begin(); it!=l.end(); it++)
	{
		cout << *it;
	}
}

