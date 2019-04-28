#include <iostream>

/*
 * Nullptr
 * To distinguish between an integer 0 and a null pointer.
 * It's an example of return type resolver idiom, which is used
 * to implement nullptr.
 * Official proposal:
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2431.pdf
 */

const 
class NullptrT
{
public:
    template<typename T>
    operator T*() const { return 0; } // for non-member pointer

    template<typename C, typename T>
    operator T C::*() const { return 0; } // for member pointer
private:
    void operator&() const;  
} Nullptr;

struct X {
    void f1(){}
};

void foo(int) { std::cout << "foo int" << std::endl; }
void foo(char*) { std::cout << "foo char*" << std::endl; }

int main()
{
    int *p1 = Nullptr;
    if(not p1) std::cout << "p1 is null" << std::endl;
    if(p1 == Nullptr) std::cout << "p1 is null" << std::endl;

    int x = 10;
    int *p2 = &x;
    if(p2 != Nullptr) std::cout << "p2 is not null" << std::endl;

    void (X::*fptr)() = Nullptr;

    foo(Nullptr);
    foo(nullptr);
    //foo(NULL);

    return 0;
}