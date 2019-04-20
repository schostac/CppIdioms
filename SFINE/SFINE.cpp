#include <iostream>
#include <type_traits>

/*
 * Substitution Failure Is Not An Error (SFINE)
 * 
 * During overload resolution of function templates,
 * when substituting the explicitly specified or deduced type 
 * for the template parameter fails, the specialization 
 * is discarded from the overload set 
 * instead of causing a compile error.
 * 
 * Substitution failure is any situation when type or 
 * expression would be ill-formed, if written using 
 * the substituted arguments.  
 * 
 * Together with 'enable-if', it is heavily used in 
 * template metaprogramming.   
 */

template <typename T>
void foo(const T &) { std::cout << "foo1" << std::endl; }

template <typename T, class U = typename T::Inner> // discarded
void foo(const T &) { std::cout << "foo2" << std::endl; }

struct X {};

int main()
{
    foo(X());
    return 0;
}
