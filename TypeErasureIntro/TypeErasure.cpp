#include <iostream>
#include <algorithm> 
#include <vector>
#include <memory>
#include <cstdlib>

/*
 * Type erasure
 * 
 * C++ is a statically typed language with strong typing.
 * 
 * In statically typed languages type of an object is known 
 * and set at compile time, while in dynamically typed languages
 * the type is associated with run-time values.
 * In strongly typed languages the type of an object doesn't change.
 * 
 * At the same time, the type erasure idiom in C++ allows usage of 
 * various concrete types through a single generic interface.
 * 
 * There is no one strict rule how to implement this idiom, it  can 
 * have various forms. In other words, we can erase type 
 * in many different ways (void*, templates, polymorphism, etc.).
 * 
 * https://en.wikipedia.org/wiki/Type_system
 * https://en.wikipedia.org/wiki/Type_erasure
 * https://en.wikipedia.org/wiki/Duck_typing
 * https://stackoverflow.com/questions/2351190/static-dynamic-vs-strong-weak
 */

namespace examples // to hide declarations from collisions
{
// 1. Type erasure using void* (like in C)
void qsort (void* base, size_t num, size_t size,
            int (*compar)(const void*,const void*));

// A separate such function is needed for each type
int compare(const void* a, const void* b)
{
    const int arg1 = *static_cast<const int*>(a);
    const int arg2 = *static_cast<const int*>(b);
    if(arg1 < arg2) return -1;
    if(arg1 > arg2) return 1;
    return 0;
};

// Drawback: not safe
// ********************************************************************


// 2. Type erasure using templates

// Duck typing: we expect that some type RandomAccessIterator behaves like
// iterator, i.e. implements operator++ and so on. Otherwise, it will not compile
template <class RandomAccessIterator>
  void sort(RandomAccessIterator first, RandomAccessIterator last);

// Drawback: may lead to many function template instantions 
// and longer compilation time
// ********************************************************


// 3. Type erasure using polymorphism
struct A {
    virtual ~A() = default;
    virtual void foo() = 0;
};

struct B : A {
    ~B() = default;
    void foo() override { std::cout << "B" << std::endl; }
};

struct C : A {
    ~C() = default;
    void foo() override { std::cout << "C" << std::endl; }
};

// We don't see a concrete type (it's erased) though can dynamic_cast
void call(A* p) { p->foo(); };

// Drawback: run-time cost (dynamic dispatch, indirection, vtable, etc.)
// *************************************************************


// 4. Type erasure using union (special class type that can hold only 
// one of its non-static data members at a time). 
struct Data {};

union U {
    Data d; // occupies 1 byte
    std::int32_t n; // occupies 4 bytes
    char c; // occupies 1 byte
    ~U() {} // need to know currently active type
}; // an instance of U in total occupies 4 bytes.

// Drawback: not safe.
// *******************
}

int main()
{
    // 1. Type erasure using void*
    std::vector<int> v2 = {3,1,2};
    std::qsort(v2.data(), v2.size(), sizeof(int), &examples::compare);
     
    // 2. Type erasure using templates
    std::vector<int> v1 = {3,1,2};
    std::sort(v1.begin(), v1.end());

    // 3. Type erasure using polymorphism
    std::unique_ptr<examples::A> ap1 = std::make_unique<examples::B>();
    std::unique_ptr<examples::A> ap2 = std::make_unique<examples::C>();
    call(ap1.get());
    call(ap2.get());

    // 4. Type erasure using union class
    examples::U u;
    u.n = 100;
    u.c; // reading c is undefined
    new(&u.d) examples::Data();

    return 0;
}