#include <iostream>

/*
 * Nullptr 
 * To distinguish between an integer 0 and a null pointer.
 * It's an example of return type resolver idiom, which is used
 * to implement nullptr.
 */

const 
class NullptrT
{
public:
    template<typename T>
    operator T*() const { return 0; }

    template<typename C, typename T>
    operator T C::*() const { return 0; }

    operator bool() const { return false; }
private:
    void operator&() const;    
} Nullptr;

int main()
{
    int * p = Nullptr;

    if(not p) std::cout << "p is null" << std::endl; 
    if(not Nullptr) std::cout << "nullptr is null" << std::endl; 

    return 0;
}
