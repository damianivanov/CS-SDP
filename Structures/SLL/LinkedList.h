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
    int _size;
    Node<T> *tail;

public:
    int get_size() { return this._size; }
    Node<T> *get_Head() { return this->head; }
    Node<T> *get_Tail() { return this->tail; }

    void add_Element(T element)
    {
        if (!head)
        {
            Node<T> *new_head = new Node<T>(element);
            new_head->next = nullptr;
            this->head = new_head;
            this->tail = new_head;
            _size++;
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
            _size++;
            BOOST_LOG_TRIVIAL(info) << "New element was added to the Linked List";
        }
    }

    void Print()
    {
        Node<T>* curr_node = head;
        while (curr_node!=NULL)
        {
            std::cout << curr_node->data << endl;
            curr_node = curr_node->next;
        }
    }

    LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->_size = 0;
    }

    ~LinkedList() {};
};
