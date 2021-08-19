#include <iostream>
#include "../containers.h"

template <typename T>
class containers::vector
{
private:
    void init_vector();
    void clear_vector();
    void upscale_vector();
    bool inside(const size_t);
    static void throw_index_error(const std::string where = "") { throw std::out_of_range(where+"IndexError: invalid array size"); };
private:
    containers::allocator<T>* mem_source;
    T *data;
    size_t length;
    size_t capacity;
    size_t scale_factor;
    static size_t init_capacity;
    static size_t init_scale_factor;
public:
public:
    vector();
    vector(T *, T *);
    ~vector();

    T& at(const size_t);
    T& operator[](const size_t i) { return data[i]; };
    containers::vector<T> &operator=(const containers::vector<T>);

    const size_t size() { return length; };
    const size_t resource() { return capacity; };
    bool empty() { return length == 0; };

    void push_back(const T &);
    void push_at(const T &, const size_t);
    void erase(const size_t);
    void erase();
    void swap(const size_t, const size_t);

    const T* begin();
    const T* end();
};

template <typename T>
size_t containers::vector<T>::init_capacity = 5;

template <typename T>
size_t containers::vector<T>::init_scale_factor = 2;

template <typename T>
containers::vector<T>::vector()
{
    init_vector();
    data = mem_source->allocate(capacity);
}

template <typename T>
containers::vector<T>::vector(T *from_begin, T *from_end)
{
    init_vector();
    length = mem_source->blocks(from_begin, from_end);
    capacity = length * scale_factor;
    data = mem_source->allocate(capacity);
    if (data==nullptr) throw_index_error();
    data = mem_source->copy(data, from_begin, from_end);
}

template <typename T>
containers::vector<T>::~vector() { clear_vector(); }

template <typename T>
void containers::vector<T>::init_vector()
{
    mem_source = new allocator<T>;
    length = 0;
    capacity = init_capacity;
    scale_factor = init_scale_factor;
    data = nullptr;
}

template <typename T>
T& containers::vector<T>::at(const size_t index)
{
    if (!inside(index)) throw_index_error();
    return data[index];
}

template <typename T>
void containers::vector<T>::clear_vector()
{
    mem_source->deallocate(data, capacity);
    delete mem_source;
}

template <typename T>
void containers::vector<T>::upscale_vector()
{
    size_t new_capacity = capacity * scale_factor;
    T* new_data = mem_source->allocate(new_capacity);
    mem_source->copy(new_data, data, capacity);
    mem_source->deallocate(data, capacity);
    data = new_data;
    capacity = new_capacity;
}

template <typename T>
bool containers::vector<T>::inside(const size_t idx) {return (idx >= 0 && idx < length); }

template <typename T>
void containers::vector<T>::push_back(const T &item)
{
    if (length < capacity) data[length] = item;
    else { upscale_vector(); push_back(item); }
    ++length;
    return;
}

template <typename T>
void containers::vector<T>::push_at(const T &item, const size_t n)
{
    if (!inside(n)) { throw_index_error(); return; }
    if (length < capacity) { for (size_t i = length; i >= n; --i) data[i] = data[i-1]; data[n] = item; }
    else { upscale_vector(); push_at(item, n); }
    ++length;
    return;
}

template <typename T>
void containers::vector<T>::erase(const size_t at)
{
    if (!inside(at)) { throw_index_error(); return; }
    for (size_t i = at; i < length; ++i) data[i] = data[i+1];
    --length;
}

template <typename T>
void containers::vector<T>::erase()
{
    length = 0;
    mem_source->deallocate(data, capacity);
    data = mem_source->allocate(capacity);
}

template <typename T>
void containers::vector<T>::swap(const size_t x, const size_t y)
{
    if (inside(x) && inside(y))
        if (x != y)
        {
            // temporary variable is actually quicker, but we can do this without it
            // data[x] ^= data[y];
            // data[y] ^= data[x];
            // data[x] ^= data[y];
            T tmp = data[x];
            data[x] = data[y];
            data[y] = tmp;
            return;
        }
    return;
}

template <typename T>
class containers::allocator
{
private:
private:
    size_t g_memory_used;

public:
public:
    allocator();
    ~allocator();

    T *allocate(const size_t);
    T *allocate(T*, T*);
    void deallocate(T *, const size_t);
    size_t blocks(T*, T*);
    T *copy(T *, T *, const T *);
    T *copy(T *, T *, const size_t);
};

template <typename T>
containers::allocator<T>::allocator() { g_memory_used = 0; }

template <typename T>
containers::allocator<T>::~allocator() {}

template <typename T>
T *containers::allocator<T>::allocate(T *begin, T* end) { return allocate(blocks(begin,end)); }

template <typename T>
T *containers::allocator<T>::allocate(const size_t n)
{
    T *allocated_now = new T[n];
    g_memory_used += n * sizeof(T);
    return allocated_now;
}

template <typename T>
void containers::allocator<T>::deallocate(T *to_clean, const size_t n)
{
    size_t items = n;
    try
    {
        delete[] to_clean;
        g_memory_used -= (n * sizeof(T));
    }
    catch (...)
    {
        std::cerr << "deallocation aborted\n";
    }
}

template <typename T>
size_t containers::allocator<T>::blocks(T* begin, T* end)
{
    size_t blocks = 1;
    T* tmp = begin;
    for ( ; tmp != end && tmp != nullptr; ++blocks, ++tmp ) { }
    if (tmp!=end || tmp==nullptr)
        throw std::out_of_range("IndexError: invalid array size");
    if (tmp==begin) --blocks;
    return blocks;
}


template <typename T>
T *containers::allocator<T>::copy(T *to, T *from_begin, const T *from_end)
{
    for (T *to_tmp = to, *tmp = from_begin; tmp != from_end + 1 && tmp != nullptr && to_tmp != nullptr; ++to_tmp, ++tmp)
        *to_tmp = *tmp;
    return to;
}

template <typename T>
T *containers::allocator<T>::copy(T *to, T *from, const size_t n)
{
    T *from_end = from + (sizeof(T) * n);
    if (from_end != nullptr)
        return copy(to, from, from_end);
    else
        throw std::out_of_range("IndexError: invalid array size");
}