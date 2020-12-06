#ifndef _LINKED_LIST_CPP
#define _LINKED_LIST_CPP
#include "DLList.h"

template<class T>
DLList<T>::DLList() {
	first = rear = nullptr;
}

template<class T>
DLList<T>::DLList(const DLList<T>& other)
{
	cpy(other);
}

template<class T>
void DLList<T>::cpy(const DLList<T>& other) {
	if (other.empty()) {
		first = rear = nullptr;
		return;
	}
	Node* ptr = other.first;
	while (ptr != nullptr)
	{
		push_back(ptr->value);
		ptr = ptr->next;
	}
}

template<class T>
void DLList<T>::clear()
{
	while (!empty())
	{
		pop_front();
	}
	first = rear = nullptr;
}

template<class T>
void DLList<T>::push_back(const T& value) {
	if (empty())
	{
		Node* tmp = new Node(value);
		first = rear = tmp;	
		return;
	}
	Node* tmp = new Node(value, rear);
	rear->next = tmp;
	rear = tmp;
}

template<class T>
void DLList<T>::push_front(const T& value) {

	if (empty())
	{
		Node* tmp = new Node(value);
		first = rear = tmp;
		return;
	}
	Node* tmp = new Node(value,nullptr,first);
	first->prev = tmp;
	first = tmp;
}

template<class T>
void DLList<T>::pop_back()
{
	if (empty()) throw std::out_of_range("The list is empty");
	
	Node* tmp=rear;
	rear = rear->prev;
	delete tmp;
	if (rear == nullptr) first = nullptr;
	else rear->next = nullptr;
}

template<class T>
void DLList<T>::pop_front()
{
	if (empty()) throw std::out_of_range("The list is empty");

	Node* tmp = first;
	first = first->next;
	delete tmp;
	if (first == nullptr) rear = nullptr;
	else first->next = nullptr;
}

template<class T>
bool DLList<T>::empty() const
{
	return first == nullptr;
}

template<class T>
typename DLList<T>::Iterator DLList<T>::begin() const
{
	return Iterator(first);
}

template<class T>
typename DLList<T>::Iterator DLList<T>::end() const
{
	return Iterator(rear);
}

template<class T>
void DLList<T>::insert(const T& value, Iterator it)
{
	if (it==begin())
	{
		push_front(value);
		return;
	}

	Node* tmp = new Node(value, it.ptr->prev, it.ptr);
	it.ptr->prev->next=tmp;
	it.ptr->prev = tmp;
}

template<class T>
void DLList<T>::insert_after(const T& value, Iterator it)
{
	if (it==end())
	{
		push_back(value);
		return;
	}
	Node* temp = new Node(value, it.ptr, it.ptr->next);
	it.ptr->next->prev = temp;
	it.ptr->next = temp;
}

template<class T>
DLList<T>::~DLList() 
{
	clear();
}

template<class T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
	if (this != &other)
	{
		clear();
		cpy(other);
	}
	return *this;
}

//------ITERATOR----------------

template<class T>
DLList<T>::Iterator::Iterator()
{
	ptr = nullptr;
}

template<class T>
DLList<T>::Iterator::Iterator(Node* other)
{
	ptr = other;
}

template<class T>
T DLList<T>::Iterator::operator*()
{
	if (ptr == nullptr) throw std::runtime_error("No value");
	return ptr->value;
}

template<class T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator++()
{
	if (ptr == nullptr) throw std::runtime_error("No element");
	ptr = ptr->next;
	return Iterator(ptr);
}

template<class T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator--()
{
	if (ptr == nullptr) throw std::runtime_error("No element");
	ptr = ptr->prev;
	return Iterator(ptr);
}

template<class T>
bool DLList<T>::Iterator::operator==(const Iterator& other) const
{
	return ptr == other.ptr;
}

template<class T>
bool DLList<T>::Iterator::operator!=(const Iterator& other) const
{
	return ptr != other.ptr;
}

template<class T>
void DLList<T>::erase(Iterator it) {
	if (it == Iterator()) return;
	if (it==begin())
	{
		pop_front();
	}
	if (it == end())
	{
		pop_back();
	}
	Node* tmp = it.ptr;
	it.ptr->prev->next = it.ptr->next;
	it.ptr->next->prev = it.ptr->prev;
	--it;
	delete tmp;
}
#endif