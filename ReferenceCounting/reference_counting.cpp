#include <iostream>
#include <utility>
#include <stdexcept>
#include <memory>


/*
 * Reference Counting
 * 
 * Manage sharing of a resource/object, and prevent 
 * expensive copying, and allow proper resource deallocation 
 * of objects that use dynamically allocated resources. 
 * 
 */

template<typename T>
class SharedState {
public:
    template <typename>
    friend class SharedPointer;
    SharedState(T *ptr_): ptr(ptr_), count(1) {
        if (not ptr) throw std::logic_error{""};
    }
    ~SharedState() { delete ptr; }
private:
    int count;
    T *ptr;
};

template<typename T>
class SharedPointer 
{
public:
    SharedPointer(): state{nullptr} {}
    SharedPointer(T *ptr): state{new SharedState<T>(ptr)} {}
    SharedPointer(const SharedPointer& other) noexcept: state{other.state} 
    {
        if(state) ++state->count;
    }
    SharedPointer& operator=(const SharedPointer& other) noexcept 
    {
        if (state and --state->count == 0) delete state;
        state = other.state;
        if(state) ++state->count;
        return *this;
    }
    ~SharedPointer() 
    {
        if (state and --state->count == 0) delete state;
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
        p3 = std::move(p2);
    }
    auto p4 = p1;
    return 0;
}