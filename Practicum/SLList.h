#include <iostream>

template<class T>
struct Node
{
	T data;
	Node* next;
};

template<class T>
class SLList
{
private:
	Node<T>* Head;
	int size;
public:
	SLList() : {this.size = 0};
	bool empty() const { return size == 0; }
	void erase();
	~SLList();
};
