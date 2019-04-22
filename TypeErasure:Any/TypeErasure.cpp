#include <iostream>
#include <iterator>
#include <set>
#include <cassert>
#include <functional>
#include <any>
#include <vector>
#include <memory>

struct Any {
   struct Base {};
    
   template<typename T>
   struct Inner: Base {
     Inner(T t): _t{t} {}
     T _t;
     static void type() {}
   };
   
   template<typename T>
   constexpr Any(T && t): 
        ptr{std::make_unique<Inner<T>>(t)}, 
        typePtr{&Inner<T>::type} 
    {}
    
   std::unique_ptr<Base> ptr = nullptr;
   void (*typePtr)() = nullptr;
   
};

template<typename T>
T* anyCast(const Any & any) 
{
    if (any.typePtr == &Any::Inner<T>::type) 
    {
        return &static_cast<Any::Inner<T>*>(any.ptr.get())->_t;
    }
    return nullptr;
}

int main()
{
    Any any(10);
    std::cout << *anyCast<int>(any) << std::endl;
    return 0;
}

