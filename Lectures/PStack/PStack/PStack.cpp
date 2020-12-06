#ifndef __PSTACK_CPP
#define __PSTACK_CPP
#include <cassert>
#include "PStack.h"

template<class T>
PStack<T>::PStack():first(nullptr)
{		

}

template<class T>
PStack<T>::~PStack()
{

}

template<class T>
PStack<T>::PStack(std::shared_ptr<node> _first):first(_first){}

template<class T>
PStack<T> PStack<T>::push(const T& x) const
{
	return PStack<T>{std::make_shared<node>(x, first)};
}

template<class T>
PStack<T> PStack<T>::pop() const
{
	assert(!empty());
	return PStack<T>{first->tail};
}

template<class T>
T PStack<T>::top() const
{
	assert(!empty());
	return first->head;
}

template<class T>
PStack<T>::node::node (const T& _head, std::shared_ptr<PStack<T>::node> _tail):head(_head),tail(_tail)
{
}

template<class T>
bool PStack<T>::empty() const 
{
	return ((bool)first == false);
}

#endif // !__PSTACK_CPP
