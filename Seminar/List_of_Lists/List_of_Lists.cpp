// List_of_Lists.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <math.h>
using namespace std;



template<class T>
list<T> createList(const list<T> &l, typename list<T>::iterator& it, int k) {

	list<T> tmp;
	for (size_t i = 0; i < k && it != l.end(); i++)
	{
		T new_data = *it;
		tmp.push_back(new_data);
		it++;
	}
	return tmp;
}

template<class T>
list<list<T>> chunk(list<T> l, int k) {
	
	list<list<T>> result;
	typename list<T>::iterator it = l.begin();
	while (it!=l.end())
	{
		result.push_back(createList(l,it,k));
	}
	return result;
}

int main()
{
	int k;
	cin >> k;
	int n;
	cin >> n;
	list<double> l;
	for (size_t i = 0; i < n; i++)
	{
		double x;
		cin >> x;
		l.push_back(x);
	}

	list<list<double>> result = chunk(l, k);
	list<list<double>>::const_iterator it = result.begin();
	list<double>::const_iterator it2;
	for (it;it !=result.end(); ++it)
	{
		for (it2 = it->begin(); it2 != it->end(); ++it2) {
			cout << *it2 << " ";
		}
		cout << endl;
	}
}


//
//template<class T>
//std::list<T> createList(const std::list<T>& ls, int k, typename std::list<T>::const_iterator& it) {
//    std::list<T> newList;
//    for (int i = 0; i < k && it != ls.end(); ++i) {
//        newList.push_back(*it);
//        it++;
//    }
//    return newList;
//}
//
//template<class T>
//std::list<std::list<T>> chunk(std::list<T> ls, int k) {
//    typename std::list<T>::const_iterator it = ls.begin();
//    std::list<std::list<T>> result;
//    while (it != ls.end()) {
//        result.push_back(createList(ls, k, it));
//    }
//    return result;
//}
//
//
//int main() {
//    std::list<double> myList;
//    for (int i = 0; i < 11; ++i) {
//        double num;
//        cin >> num;
//        myList.push_back(num);
//    }
//
//    std::list<std::list<double>> result = chunk(myList, 4);
//    std::list<std::list<double>>::const_iterator it = result.begin();
//    std::list<double>::const_iterator it2;
//    for(it; it != result.end(); ++it){
//        for(it2 = it->begin(); it2 != it->end(); ++it2){
//            cout << *it2 << " ";
//        }
//        cout << endl;
//    }
//
//    return 0;
//}
