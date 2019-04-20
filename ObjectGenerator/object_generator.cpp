#include <iostream>
#include <utility>
#include <tuple>

/*
 * Object Generator
 * 
 * Used to simplify creation of objects without 
 * explicitly specifying their types.
 */

template<typename... Args>
auto makeTuple(Args&&... args) // Like std::make_tuple
{
    return std::tuple<Args...>(std::forward<Args>(args)...);
}

int main()
{
    std::tuple<int, std::string, char> t1 = std::tuple<int, std::string, char>(10, std::string{"text"}, 'x');
    auto t2 = makeTuple(10, std::string{"text"}, 'x');
    std::cout << std::boolalpha << (t1 == t2) << std::endl;
    return 0;
}