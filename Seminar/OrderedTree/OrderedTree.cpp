#include <iostream>

class OrderedTree
{
private:
    struct Node
    {
        int data;
        Node *left;
        Node *right;
        Node(int data, Node *left = nullptr, Node *right = nullptr) : data(data), left(left), right(right) {}
    };

    Node *root;
    Node *copyTree(const Node *node)
    {
        if (node == nullptr)
            return nullptr;

        Node *tmp = new Node(node->data);
        tmp->left = copyTree(node->left);
        tmp->right = copyTree(node->right);
        return tmp;
    }
    void deleteTree(Node *node)
    {
        if (node == nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    void insertHelper(Node *&node, int data)
    {
        if (node == nullptr)
        {

            node = new Node(data);
            return;
        }
        data <= node->data ? insertHelper(node->left, data) : insertHelper(node->right, data);
    }
    void printHelper(Node *node)
    {
        if (node == nullptr)
            return;

        printHelper(node->left);
        std::cout << node->data << " ";
        printHelper(node->right);
    }

public:
    OrderedTree() : root(nullptr) {}
    OrderedTree(int data)
    {
        root = new Node(data);
    }
    OrderedTree(const OrderedTree &other)
    {
        root = copyTree(other.root);
    }
    ~OrderedTree() { deleteTree(root); }
    OrderedTree &operator=(const OrderedTree &other)
    {
        if (this != &other)
        {
            deleteTree(root);
            root = copyTree(other.root);
        }

        return *this;
    }
    void insert(int data)
    {
        insertHelper(root, data);
    }
    void print()
    {
        printHelper(root);
        std::cout << "\n";
    }
};

int main()
{
    OrderedTree ot;
    ot.insert(7);
    ot.insert(6);
    ot.insert(4);
    ot.insert(11);
    ot.insert(13);
    ot.print();
    return 0;
}