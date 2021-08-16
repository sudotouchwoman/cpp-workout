#include <iostream>
#include <exception>

namespace containers
{
    template <typename T> class queue;
};

template <typename T>
class containers::queue
{
private:
    struct node
    {
        T data;
        node* next;
    };
    void init_queue();
    void clear_queue();
private:
    int length;
    node* queue_head;
    node* queue_tail;
public:
    queue();
    ~queue();
    void print();
    void push_back(const T);
    T& pop_front();
    int size();
    bool empty();
};

template <typename T>
void containers::queue<T>::init_queue()
{
    queue_head = nullptr;
    queue_tail = nullptr;
    length = 0;
}

template <typename T>
void containers::queue<T>::clear_queue()
{
    node* tmp = queue_head;
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
containers::queue<T>::queue()
{
    init_queue();
}

template <typename T>
containers::queue<T>::~queue()
{
    if (queue_head != nullptr) clear_queue();
}

template <typename T>
void containers::queue<T>::print()
{
    std::cout << "queue:\t";
    for (node* tmp = queue_head; tmp!= nullptr; tmp = tmp->next){ std::cout << tmp->data << ' '; }
    std::cout << '\n';
    return;
}

template <typename T>
void containers::queue<T>::push_back(const T item)
{
    node* newnode = new node;
    newnode->data = item;
    newnode->next = nullptr;
    if (empty())
    {
        queue_head = newnode;
        queue_tail = newnode;
    }
    else
    {
        queue_tail->next = newnode;
        queue_tail = newnode;
    }
    ++length;
    return;
}

template <typename T>
T& containers::queue<T>::pop_front()
{
    if (empty())
    {
        throw std::out_of_range("Out of range: Attempt to pop from empty queue");
    }
    --length;
    T& popped_front = queue_head->data;
    node* former_head = queue_head;
    queue_head = queue_head->next;
    delete former_head;
    return popped_front;
}

template <typename T>
int containers::queue<T>::size() { return length; }

template <typename T>
bool containers::queue<T>::empty() { return (length==0); }