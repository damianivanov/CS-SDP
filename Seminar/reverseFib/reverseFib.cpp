#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;


template<class T>
struct Node {
    T data;
    Node* next;
};

template<class T>
int count(Node<T>* first, T elem) {
    Node<T>* curr = first;
    int counter = 0;
    while (curr) {
        if (curr->data == elem) {
            counter++;
        }
        curr = curr->next;
    }
    return counter;
}

template<class T>
void remove(Node<T>*& list, T x) {
    if (list == nullptr) {
        return;
    }
    Node<T>* toDelete = nullptr;

    // premahvame ako pyrviqt element e raven na x
    while (list != nullptr && list->data == x) {
        toDelete = list;
        list = list->next;
        delete toDelete;
    }
    if (list == nullptr) {
        return;
    }
    Node<T>* curr = list;
    while (curr->next != nullptr) {
        if (curr->next->data == x) {
            toDelete = curr->next;
            curr->next = curr->next->next;
            delete toDelete;
        }
        else {
            curr = curr->next;
        }
    }
}

template<class T>
void removeDuplictes(Node<T>*& first) {
    while (first != nullptr && count(first, first->data) > 1) {
        remove(first, first->data);
    }

    if (first == nullptr) {
        return;
    }

    Node<T>* curr = first;
    while (curr->next != nullptr) {
        if (count(curr->next, curr->next->data) > 1) {
            remove(curr->next, curr->next->data);
        }
        else {
            curr = curr->next;
        }
    }

    //    if (first == nullptr || first->next == nullptr) {
    //        return;
    //    }
    //    Node<T> *current = first;
    //    Node<T> *current2 = first;
    //    while (current->next != nullptr) {
    //        current2 = current;
    //        while (current2->next != nullptr) {
    //            if (current->data == current2->next->data) {
    //                remove(first, current2->next->data);
    //            }
    //            current2 = current2->next;
    //        }
    //        current = current->next;
    //    }
}


using pred = function<bool(int)>;

void split(Node<int>* L, pred p, Node<int>*& L1, Node<int>*& L2) {
    L1 = nullptr;
    L2 = nullptr;
    if (L == nullptr) {
        return;
    }

    while (L != nullptr) {
        if (p(L->data)) {
            L1 = new Node<int>{ L->data, L1 };
        }
        else {
            L2 = new Node<int>{ L->data, L2 };
        }
        L = L->next;
    }
}


void split2(Node<int>* L, pred p, Node<int>*& L1, Node<int>*& L2) {
    L1 = nullptr;
    L2 = nullptr;
    if (L == nullptr) {
        return;
    }

    Node<int> dummy1{ -1, nullptr },
        dummy2{ -1, nullptr },
        * l1Tail = &dummy1,
        * l2Tail = &dummy2;

    while (L != nullptr) {
        if (p(L->data)) {
            l1Tail->next = new Node<int>{ L->data, nullptr };
            l1Tail = l1Tail->next;
        }
        else {
            l2Tail->next = new Node<int>{ L->data, nullptr };
            l2Tail = l2Tail->next;
        }
        L = L->next;
    }

    L1 = dummy1.next;
    L2 = dummy2.next;
}


template<class T>
Node<T>* reverseFib(Node<T>* first) {
    Node<T>* current = first;

    if (current == nullptr) {
        return nullptr;
    }

    if (first->next == nullptr) {
        return new Node<T>{ first->data, nullptr };
    }
    Node<T>* result = nullptr;
    result = new Node<T>{ current->data, nullptr };
    while (current->next->next != nullptr) {
        if ((current->data + current->next->data) != current->next->next->data) {
            return nullptr;
        }
        current = current->next;
        result = new Node<T>{ current->data, result };   //push front
    }
    current = current->next;
    result = new Node<T>{ current->data, result };
    return result;
}

//template<class T>
//void *push(Node<T> *first, const int &x) {
//
//}

Node<int>* createFibList(unsigned int n) {
    //0 1 1 2 3 5 8;
    if (n == 0) { return nullptr; }
    Node<int>* firstFib = new Node<int>{ 0, nullptr };
    if (n == 1) { return firstFib; }
    Node<int>* lastFib = firstFib;

    firstFib->next = new Node<int>{ 1, nullptr };
    lastFib = firstFib->next;

    int a = 0, b = 1;
    for (int i = 2; i < n; ++i) {
        lastFib->next = new Node<int>{ a + b, nullptr };
        lastFib = lastFib->next;
        int save = a + b;
        a = b;
        b = save;
    }
    return firstFib;
}

template<class T>
void reverse(Node<T>* first) {
    Node<T>* current = first;
    Node<T>* prev = nullptr, * next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    first = prev;
}

template<class T>
void print(Node<T>* first) {
    Node<T>* current = first;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

void testFibList() {
    print(reverseFib(createFibList(11)));
    print(createFibList(5));
    print(createFibList(8));
    print(createFibList(0));
    print(createFibList(1));
    print(createFibList(2));
}

bool odd(int x) {
    return x % 2 == 1;
}

//int main() {
////    testFibList();
////    Node<int> fifth{1, nullptr};
////    Node<int> fourth{5, &fifth};
////    Node<int> third{5, &fourth};
////    Node<int> second{6, &third};
////    Node<int> first{4, &second};
//
//    Node<int> *L1 = nullptr;
//    Node<int> *L2 = nullptr;
////
////    split(&first, &odd, L1, L2);
////
////    print(L1);
//
//    Node<int> *list = new Node<int>{1, new Node<int>{2, new Node<int>{3, new Node<int>{4, nullptr}}}};
//
//    split2(list, &odd, L1, L2);
//    print(L1);
//    print(L2);
//
////    removeDuplictes(list);
////    print(list);
//
//    return 0;
//}