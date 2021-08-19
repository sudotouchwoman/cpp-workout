#include <iostream>
#include <exception>
#include "../containers.h"

template <typename T>
class containers::stack
{
private:
    struct node
    {
        T data;
        node* next;
    };
    void init_stack();
    void clear_stack();
private:
    int length;
    node* stack_head;
public:
    stack();
    ~stack();
    void print();
    void push(const T);
    T& pop();
    int size();
    bool empty();
};

template <typename T>
void containers::stack<T>::init_stack()
{
    stack_head = nullptr;
    length = 0;
}

template <typename T>
void containers::stack<T>::clear_stack()
{
    node* tmp = stack_head;
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
containers::stack<T>::stack()
{
    init_stack();
}

template <typename T>
containers::stack<T>::~stack()
{
    if (stack_head != nullptr) clear_stack();
}

template <typename T>
void containers::stack<T>::print()
{
    std::cout << "stack:\t";
    for (node* tmp = stack_head; tmp!= nullptr; tmp = tmp->next){ std::cout << tmp->data << ' '; }
    std::cout << '\n';
    return;
}

template <typename T>
void containers::stack<T>::push(const T item)
{
    ++length;
    node* newnode = new node;
    newnode->data = item;
    newnode->next = stack_head;
    stack_head = newnode;
    return;
}

template <typename T>
T& containers::stack<T>::pop()
{
    if (empty())
    {
        throw std::out_of_range("Out of range: Attempt to pop from empty stack");
    }
    --length;
    T& popped = stack_head->data;
    node* former_head = stack_head;
    stack_head = stack_head->next;
    delete former_head;
    return popped;
}

template <typename T>
int containers::stack<T>::size() { return length; }

template <typename T>
bool containers::stack<T>::empty() { return (length==0); }