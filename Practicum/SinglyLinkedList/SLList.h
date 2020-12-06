#pragma once
#include <iostream>

template<class T>
struct Node
{

	T data;
	Node* next;
	Node(T data)
	{
		this->data = data;	
		this->next = nullptr;
	}
	~Node()
	{
		delete this->next;
	}
};

template<class T>
class SLList
{
private:
	Node<T>* Head;
	int size;
public:
	SLList(): size(0) {}
	SLList(const SLList& other) { copyFrom(other); }
	bool empty() const { return size == 0; }

	void copyFrom(const SLList<T>& other)
	{
		if (!Head)
		{
			//The List is not empty
		}

		Head = new Node<T>(other.Head->data);
		Node<T>* curr = other.Head; //other iterator
		Node<T>* new_curr = this->Head; //current iterator

		while (curr->next!=nullptr)
		{	
			Node<T>* to_push = new Node<T>(curr->next->data);
			new_curr->next = to_push;

			new_curr = new_curr->next;
			curr = curr->next;
			size++;
		}
	}
	//Find(const T& data)
	void erase() 
	{
		Node<T>* curr = this->Head;
		while (curr->next != nullptr)
		{
			Node<T>* to_delete = curr->next;
			to_delete->next = nullptr;
			delete to_delete;
			curr = curr->next;
			size--;
		}
		this->Head->next = nullptr;
	}
	void push_back(const T& element)
    {
        Node<T> *new_node = new Node<T>(element);

        if (!this->Head)
        {
            new_node->next = nullptr;
            this->Head = new_node;    
        }
        else
        {
			Node<T>* curr = Head;
			while (curr->next!=nullptr)
			{
				curr = curr->next;
			}
			curr->next = new_node;
        }
			size++;
    }
	void print()
	{
		Node<T>* curr_node = Head;
		while (curr_node != nullptr)
		{
			std::cout << curr_node->data <<"\n";
			curr_node = curr_node->next;
		}
	}
	
	~SLList() {
		this->erase();
	};
};
