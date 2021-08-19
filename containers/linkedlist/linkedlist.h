#include "../containers.h"
#include <iostream>
#include <exception>

template <typename T>
class containers::linkedlist
{
private:
    struct node
    {
        T data;
        node* prev;
        node* next;
    };
    void init_linkedlist();
    void clear_linkedlist();
    node* traverse(const size_t);
    node* traverse_forward(const size_t);
    node* traverse_reverse(const size_t);
    bool within(const size_t);
private:
    size_t length;
    node* linkedlist_head;
    node* linkedlist_tail;
public:
    linkedlist();
    ~linkedlist();
    void print();
    void append(const T&);
    T remove(const size_t);
    T& at(const size_t);
    T& operator[](const size_t);
    size_t size();
    bool empty();
};

template <typename T>
void containers::linkedlist<T>::init_linkedlist()
{
    linkedlist_head = nullptr;
    linkedlist_tail = nullptr;
    length = 0;
}

template <typename T>
void containers::linkedlist<T>::clear_linkedlist()
{
    if (linkedlist_head == nullptr) return;
    node* tmp = linkedlist_head;
    node* to_remove = tmp;
    while (tmp!= nullptr)
    {
        tmp = tmp->next;
        delete to_remove;
        to_remove = tmp;
    }
    delete tmp;
}

template <typename T>
containers::linkedlist<T>::linkedlist()
{
    init_linkedlist();
}

template <typename T>
containers::linkedlist<T>::~linkedlist()
{
    clear_linkedlist();
}

template <typename T>
void containers::linkedlist<T>::print()
{
    std::cout << "Contents of list:\t";
    for (node* tmp = linkedlist_head; tmp!= nullptr; tmp = tmp->next){ std::cout << tmp->data << ' '; }
    std::cout << '\n';
    return;
}

template <typename T>
void containers::linkedlist<T>::append(const T& item)
{
    node* newnode = new node;
    newnode->data = item;
    newnode->next = nullptr;
    newnode->prev = nullptr;
    if (empty())
    {
        linkedlist_head = newnode;
        linkedlist_tail = newnode;
    }
    else
    {
        newnode->prev = linkedlist_tail;
        linkedlist_tail->next = newnode;
        linkedlist_tail = newnode;
    }
    ++length;
    return;
}

template <typename T>
T containers::linkedlist<T>::remove(const size_t idx)
{
    if (!within(idx))
    {
        throw std::out_of_range("Out of range: IndexError");
    }
    node* to_remove = traverse(idx);
    node* left = to_remove->prev;
    node* right = to_remove->next;
    if (idx == 0) linkedlist_head = linkedlist_head->next;
    if (idx == length) linkedlist_tail = linkedlist_tail->prev;
    if (left != nullptr) left->next = right;
    if (right != nullptr) right->prev = left;
    T cut = to_remove->data;
    delete to_remove;
    --length;
    return cut;
}

template <typename T>
T& containers::linkedlist<T>::at(const size_t idx)
{
    if (!within(idx))
    {
        throw std::out_of_range("Out of range: IndexError");
    }
    return traverse(idx)->data;
}

template <typename T>
T& containers::linkedlist<T>::operator[](const size_t idx) { return at(idx); }

template <typename T>
struct containers::linkedlist<T>::node* containers::linkedlist<T>::traverse(const size_t idx)
{
    return (idx > length/2) ? traverse_reverse(idx) : traverse_forward(idx);
}

template <typename T>
struct containers::linkedlist<T>::node* containers::linkedlist<T>::traverse_forward(const size_t idx)
{
    node* tmp = linkedlist_head;
    for(size_t i = 0; tmp != nullptr && i < idx; ++i, tmp = tmp->next) {}
    return tmp;
}

template <typename T>
struct containers::linkedlist<T>::node* containers::linkedlist<T>::traverse_reverse(const size_t idx)
{
    node* tmp = linkedlist_tail;
    for(size_t i = length-1; tmp != nullptr && i > idx; --i, tmp = tmp->prev) {}
    return tmp;
}

template <typename T>
bool containers::linkedlist<T>::within(const size_t idx) { return (idx <= length && idx >= 0); }

template <typename T>
size_t containers::linkedlist<T>::size() { return length; }

template <typename T>
bool containers::linkedlist<T>::empty() { return (length==0); }