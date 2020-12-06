#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H
#include <stdexcept>

template<class T>
class DLList
{

private:

	struct Node
	{
		T value;
		Node* prev;
		Node* next;
		Node(const T& value, Node* _prev = nullptr, Node* _next = nullptr) : value(value) {

			prev = _prev;
			next = _next;
		}
	};
	Node* first, * rear;
	void cpy(const DLList<T>&);
	void clear();

public:
	DLList();
	DLList(const DLList<T>&);
	DLList<T>& operator=(const DLList<T>&);
	~DLList();

	void push_back(const T&);
	void pop_back();
	void pop_front();
	void push_front(const T&);
	bool empty() const;

	class Iterator
	{
	private:
		Node* ptr;
		Iterator(Node*);

	public:
		Iterator();
		T operator*();
		Iterator operator++();
		Iterator operator--();
		bool operator==(const Iterator& other) const;
		bool operator!=(const Iterator& other) const;

		friend DLList;
	};



	Iterator begin() const;
	Iterator end() const;

	void insert(const T&, Iterator);
	void insert_after(const T&, Iterator);

	void erase(Iterator);
};
#include "DLList.cpp"

#endif

