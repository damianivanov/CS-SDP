#include <boost/log/trivial.hpp>
template <typename T>
struct Node
{
    Node *next;
    T data;

    Node(T data)
    {
        this->data = data;
    }
    ~Node()
    {
        delete this->next;
    }
};

template <typename T>
class LinkedList
{
private:
    Node<T> *head;
    int size;
    Node<T> *tail;

public:
    int length() { return this->size; }
    Node<T> *get_Head() { return this->head; }
    Node<T> *get_Tail() { return this->tail; }

    void add_element(T element)
    {
        if (!head)
        {
            Node<T> *new_head = new Node<T>(element);
            new_head->next = nullptr;
            this->head = new_head;
            this->tail = new_head;
            size++;
            BOOST_LOG_TRIVIAL(info) << "Head was added to the Linked List";
            BOOST_LOG_TRIVIAL(info) << "New element was added to the Linked List";
            BOOST_LOG_TRIVIAL(info) << "Tail was added to the Linked List";
            
        }
        else
        {
            Node<T>* new_node = new Node<T>(element);
            this->tail->next = new_node;
            this->tail = new_node;
            this->tail->next = nullptr;
            size++;
            BOOST_LOG_TRIVIAL(info) << "New element was added to the Linked List";
        }
    }
    void remove_at(int index)
    {
		if (index >= _size)
        {
            BOOST_LOG_TRIVIAL(info) << "Invalid index";
        }
        Node<T>* currNode=head;
        for (size_t i = 0; i < index-1; i++)
        {
            currNode = currNode->next;
        }
        currNode->next = currNode->next->next;
        BOOST_LOG_TRIVIAL(info) << "Removed element from Linked List";
    }
    void insert_at(int index, T element)
    {
        Node<T>* newNode = new Node<T>(element);
        if (index == _size - 1)
        {
            Node<T>* curr = tail;
            tail->next = newNode;
            newNode->next = nullptr;
        }
        else {
            Node<T>* curr = head;
            for (size_t i = 0; i < index - 1; i++)
            {
                curr = curr->next;
            }
            newNode->next = curr->next;
            curr->next = newNode;
        }
    }
    T get_element_at(int index) {
        Node<T>* curr = head;
        for (size_t i = 0; i < index; i++)
        {
            curr = curr->next;
        }
        return curr->data;
        
    }
    void print()
    {
        Node<T>* curr_node = head;
        while (curr_node!=nullptr)
        {
            std::cout << curr_node->data << endl;
            curr_node = curr_node->next;
        }
    }

    LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    ~LinkedList() {};
};
