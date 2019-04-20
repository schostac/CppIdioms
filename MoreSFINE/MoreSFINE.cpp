#include <iostream>

/*
 * Substitution Failure Is Not An Error (SFINE)
 * (another example)
 */

template <typename T>
void foo(const T &) { 
    std::cout << "T not templatized" << std::endl; 
}

template <template <typename> class T, class U>
void foo(const T<U> &) {
    std::cout << "T templatized" << std::endl; 
}

struct X{};

int main()
{
    foo(X());
    return 0;
}
