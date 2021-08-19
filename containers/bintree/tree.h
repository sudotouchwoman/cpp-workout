#include "../containers.h"
#include <iostream>

template <typename T>
class containers::binary_tree
{
private:
    struct node
    {
        T data;
        node *left;
        node *right;
    };
    node *allocate();
    void deallocate(node *);
    void init_tree();
    void clear_tree(node*);
    node *walk_breadth(const node *);
    node *walk_depth(const node *);
    void insert_levelwise(const T);
    void insert_depthwise(const T);
    size_t subtree_height(node *);
    node *first_nil_breadth(const T, const node *);
    static void print_level(size_t);
private:
    node *body;
    size_t entities;
    size_t h;
public:
public:
    binary_tree();
    binary_tree(const containers::vector<T>);
    binary_tree(const T *, const size_t);
    ~binary_tree();

    void put(const T);
    T &get();
    bool contains(const T &);

    size_t height();
};

template <typename T>
containers::binary_tree<T>::binary_tree()
{
}

template <typename T>
containers::binary_tree<T>::~binary_tree()
{
}

template <typename T>
void containers::binary_tree<T>::init_tree()
{
    entities = 0;
    body = defs::NIL;
}

template <typename T>
void containers::binary_tree<T>::clear_tree(node* to_clear)
{
    if (to_clear->left != defs::NIL) clear_tree(to_clear->left);
    if (to_clear->right != defs::NIL) clear_tree(to_clear->right);
    deallocate(to_clear);
    return;
}

template <typename T>
containers::binary_tree<T>::node *containers::binary_tree<T>::allocate()
{
    node *new_node = new node;
    new_node->data = defs::NIL;
    new_node->left = defs::NIL;
    new_node->right = defs::NIL;
    return new_node;
}

template <typename T>
void containers::binary_tree<T>::deallocate(node *to_delete)
{
    if (to_delete->data != defs::NIL)
        delete to_delete->data;
    delete to_delete;
    return;
}

template <typename T>
void containers::binary_tree<T>::insert_levelwise(const T item)
{
}





template <typename T>
containers::binary_tree<T>::node *containers::binary_tree<T>::first_nil_breadth(const T item, const node *parent)
{
    for (size_t level = height(); level > 0; --level)
    {

    }
}

template <typename T>
containers::binary_tree<T>::node *containers::binary_tree<T>::walk_breadth(const node *parent)
{
    std::cout << (parent->data != defs::NIL ? parent->data : " empty node (how?) ");
}

template <typename T>
containers::binary_tree<T>::node *containers::binary_tree<T>::walk_depth(const node *parent)
{
    if (parent == defs::NIL)
    {
        std::cout << " NIL ";
        return parent;
    }
    if (parent->left != defs::NIL)
        walk_depth(parent->left);
    if (parent->right != defs::NIL)
        walk_depth(parent->right);
    if (parent->left == defs::NIL && parent->right == defs::NIL)
    {
        std::cout << (parent->data != defs::NIL ? parent->data : " empty node (how?) ");
        return parent;
    }
}

template <typename T>
size_t containers::binary_tree<T>::height()
{
    return subtree_height(body);
}

template <typename T>
size_t containers::binary_tree<T>::subtree_height(node* parent)
{
    size_t left_height = 0;
    size_t right_height = 0;
    if (parent->left != defs::NIL)  left_height = subtree_height(parent->left);
    if (parent->right != defs::NIL) right_height = subtree_height(parent->right);
    return ( left_height > right_height ? left_height : right_height );
}