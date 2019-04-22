#include <iostream>
#include <stdexcept>

/*
 * Reference Counting
 * 
 * Used to manage sharing of resource, prevent 
 * expensive copying, and allow proper resource deallocation.
 * For example, std::shared_ptr
 * 
 * Below is simple implementation, without 
 * thread-safe counters, optimization,
 * custom allocator, and interface as
 * as in std::shared_ptr.
 */

template<typename T>
class SharedState 
{
public:
    template <typename>
    friend class SharedPointer;
    SharedState(T *ptr_): ptr(ptr_), count(1) 
    {
        if (not ptr) throw std::logic_error{""};
    }
    ~SharedState() { delete ptr; }
private:
    T *ptr;
    int count;
};

template<typename T>
class SharedPointer
{
public:
    SharedPointer():state{nullptr} {}
    SharedPointer(T *ptr): state(new SharedState<T>(ptr)) {}
    ~SharedPointer() 
    {
        if(state and --state->count == 0) delete state;
    }
    SharedPointer(const SharedPointer &other): state{other.state} 
    {
        if(state) ++state->count;   
    }
    SharedPointer& operator=(const SharedPointer &other)
    {
        if(state and --state->count == 0) delete state;
        state = other.state;
        if(state) ++state->count;
        return *this;
    }
private:
    SharedState<T> *state;
};

struct Data
{
    Data() { std::cout << "Data constructor" << std::endl; }
    ~Data() { std::cout << "Data destructor" << std::endl; }
};

int main()
{
    auto p1 = SharedPointer<Data>(new Data());
    {
        auto p2 = p1;
        auto p3 = SharedPointer<Data>();
        p3 = p2;
    }
    auto p4 = SharedPointer<Data>(new Data());
    auto p5 = p1;
    return 0;
}