#include <iostream>
#include <type_traits>

/*
 * Enable-if
 * It is used to allow function overloading based on 
 * arbitrary properties of type. Relies on SFINE
 * (if invalid argument or return type is formed during 
 * instantiation of function template, the instantiation 
 * is removed instead of compilation error).
 * Often used in C++ template metaprogramming, 
 * Boost libraries, and C++ STL.
 */


template<bool>
struct EnableIf {};

template<>
struct EnableIf<true> {
    using type = void;
};

template <class T>
void foo(T) { 
    std::cout << "T is signed" << std::endl; 
}

template <class T, class = typename EnableIf<std::is_unsigned<T>::value>::type>
void foo(T) {
    std::cout << "T is unsigned" << std::endl; 
}


struct A {};

struct B : A {};

template<class T, class = typename std::enable_if<std::is_base_of<A, T>::value>::type>
struct C: T {};


int main()
{
    int x = 5;
    foo(x);

    C<B> c;

    return 0;
}