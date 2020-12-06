#include <iostream>
#include <vector>

template <typename T>
struct Node {
    T data;
    Node * next {nullptr};

    Node(T data) : data{data} { }
};

template <typename T>
void print(const Node<T> * head)
{
    const Node<T> * current = head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <typename T>
Node<T> * fromVector(std::vector<T> const& vec)
{
    Node<T> * result = nullptr;
    Node<T> * current = nullptr;

    for (T const& el : vec)
    {
        Node<T> * newNode = new Node<T>(el);
        if (result == nullptr)
        {
            // first element
            result = newNode;
            current = newNode;
        }
        else
        {
            current->next = newNode;
            current = newNode;
        }
    }
    return result;
}

template <typename T>
void deleteList(Node<T> *& head) // not ok, why?
{
    Node<T> * current = head;
    while (current != nullptr)
    {
        Node<T> * temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

template <typename T>
bool checkEqual(Node<T> *head, Node<T> *expectedList)
{
    Node<T> *current = head, *expCurrent = expectedList;
    while (current != nullptr && expCurrent != nullptr && current->data == expCurrent->data)
    {
        current = current->next;
        expCurrent = expCurrent->next;
    }
    return expCurrent == nullptr && current == nullptr;
}

template <typename T>
void testEqual(Node<T> *head, std::vector<T> const& expected)
{
    Node<T> *expectedList = fromVector(expected);
    if (checkEqual(head, expectedList))
    {
        std::cout << "<--  Test PASSED  -->\n";
    }
    else
    {
        std::cout << "<-- Test FAILED -->\n";
        std::cout << "Expected: "; print(expectedList);
        std::cout << "Got:      "; print(head);
    }
    deleteList(expectedList);
}

// Move the first node from source, to the front
// of destination
// source: 1 2 3, dest: 4 5 -> source: 2 3, dest: 1 4 5
template<typename T>
void moveNode(Node<T> **dest, Node<T> **source)
{
    // TODO
}

template <typename T>
void alternatingSplit(Node<T> **head, Node<T> **aList, Node<T> **bList)
{
    // TODO
}

// Merges two lists alternating their nodes
// Example: a = [1,7,9], b=[2,3,4], result=[1,2,7,3,9,4]
// Hint: use moveNode
template <typename T>
Node<T> *shuffleMerge(Node<T> *a, Node<T> *b)
{
    return nullptr;
}

// Merges two sorted lists into one (sorted) list
// Example: a = [1,5,7], b = [2,3,9], merged = [1,2,3,5,7,9]
template<typename T>
void sortedMerge(Node<T> **merged, Node<T> *&a, Node<T> *&b) {
    // TODO
}

// sorted merge using recursion
template <typename T>
Node<T>* mergeReq(Node<T> * a, Node<T> * b)
{
    return nullptr;
}

template <typename T>
void frontBackSplit(Node<T> ** head, Node<T> ** front, Node<T> ** back)
{
    if (*head == nullptr)
    {
        *front = *back = nullptr;
        return;
    }
    Node<T> *slow = *head, *fast = *head;
    while (fast != nullptr && fast->next != nullptr && fast->next->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    *front = *head;
    *back = slow->next;
    slow->next = nullptr;
}

template <typename T>
void mergeSort(Node<T> **head)
{
    // TODO
}

template <typename T>
void reverse(Node<T> **head)
{
    Node<T>* current = *head;
        Node<T> *prev = NULL, *next = NULL;
 
        while (current != NULL) {
           
            next = current->next;
 
            
            current->next = prev;
 
            
            prev = current;
            current = next;
        }
        head = prev;
}

template<typename T>
Node<T> *reverseReq(Node<T> **list, Node<T> *head)
{
    return nullptr;
}

int main()
{
    std::cout << "Test moveNode()\n";
    Node<int> *l1 = fromVector(std::vector<int>{1,2,3});
    Node<int> *l2 = fromVector(std::vector<int>{4,5});
    moveNode(&l1, &l2);
    testEqual(l1, std::vector<int>{4,1,2,3});
    testEqual(l2, std::vector<int>{5});
    moveNode(&l1, &l2);
    testEqual(l1, std::vector<int>{5,4,1,2,3});
    testEqual(l2, std::vector<int>{});
    moveNode(&l1, &l2);
    testEqual(l1, std::vector<int>{5,4,1,2,3});
    testEqual(l2, std::vector<int>{});
    deleteList(l1); deleteList(l2);

    std::cout << "Test alternatingSplit \n";
    Node<int> *l = fromVector(std::vector<int>{0,1,2,3,4,5,6});
    alternatingSplit(&l, &l1, &l2);
    testEqual(l1, std::vector<int>{6,4,2,0});
    testEqual(l2, std::vector<int>{5,3,1});
    deleteList(l); deleteList(l1); deleteList(l2);

    std::cout << "Test shuffleSplit \n";
    l1 = fromVector(std::vector<int>{1,2,3});
    l2 = fromVector(std::vector<int>{4,5,6});
    l = shuffleMerge(l1, l2);
    testEqual(l, std::vector<int>{1,4,2,5,3,6});
    deleteList(l);
    l1 = fromVector(std::vector<int>{1,2,3});
    l2 = fromVector(std::vector<int>{});
    l = shuffleMerge(l1, l2);
    testEqual(l, std::vector<int>{1,2,3});
    deleteList(l);
    l1 = fromVector(std::vector<int>{});
    l2 = fromVector(std::vector<int>{4,5,6});
    l = shuffleMerge(l1, l2);
    testEqual(l, std::vector<int>{4,5,6});
    deleteList(l);
    l1 = fromVector(std::vector<int>{1,2,3,7,8,9});
    l2 = fromVector(std::vector<int>{4,5,6});
    l = shuffleMerge(l1, l2);
    testEqual(l, std::vector<int>{1,4,2,5,3,6,7,8,9});
    deleteList(l);
    l1 = fromVector(std::vector<int>{1,2,3});
    l2 = fromVector(std::vector<int>{4,5,6,7,8,9});
    l = shuffleMerge(l1, l2);
    testEqual(l, std::vector<int>{1,4,2,5,3,6,7,8,9});
    deleteList(l);

    std::cout << "Test sortedMerge \n";
    l1 = fromVector(std::vector<int>{1,7,9});
    l2 = fromVector(std::vector<int>{4,5,8});
    l = mergeReq(l1, l2);
    testEqual(l, std::vector<int>{1,4,5,7,8,9});
    deleteList(l);
    l2 = fromVector(std::vector<int>{1,7,9});
    l1 = fromVector(std::vector<int>{4,5,8});
    l = mergeReq(l1, l2);
    testEqual(l, std::vector<int>{1,4,5,7,8,9});
    deleteList(l);
    l2 = fromVector(std::vector<int>{1,3});
    l1 = fromVector(std::vector<int>{4,5});
    sortedMerge(&l, l1, l2);
    testEqual(l, std::vector<int>{1,3,4,5});
    deleteList(l);

    std::cout << "Test merge sort \n";
    l = fromVector(std::vector<int>{4,5,2,7,6,1,3});
    mergeSort(&l);
    testEqual(l, std::vector<int>{1,2,3,4,5,6,7});
    deleteList(l);
    l = fromVector(std::vector<int>{});
    mergeSort(&l);
    testEqual(l, std::vector<int>{});
    deleteList(l);

    std::cout << "Test reverse \n";
    l = fromVector(std::vector<int>{1,2,3,4,5,6});
    reverse(&l);
    testEqual(l, std::vector<int>{6,5,4,3,2,1});
    l = fromVector(std::vector<int>{1,2,3,4,5,6});
    deleteList(l);
    return 0;
}
