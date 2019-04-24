#include <iostream>
#include <stdexcept>
#include <functional>
#include <variant> 
#include <vector>
#include <any>

/*
 * Type erasure (examples from std)
 * 
 * https://en.cppreference.com/w/cpp/utility/any
 * https://en.cppreference.com/w/cpp/utility/variant
 * https://en.cppreference.com/w/cpp/utility/functional/function
 * 
 * https://en.wikipedia.org/wiki/Algebraic_data_type
 * https://en.wikipedia.org/wiki/Tagged_union
 */

int main()
{
    // 1. std::any (type-safe container for single values of any type)
    std::any a;
    a = 10;
    std::cout << std::any_cast<int>(a) << std::endl;
    a = std::string{"text"};
    std::cout << std::any_cast<std::string>(a) << std::endl;

    // 2. std::variant (type-safe union)
    std::variant<int, std::string, char, long> v;
    v = 10;
    std::cout << std::get<int>(v) << std::endl;
    v = std::string{"text"};
    std::cout << std::get<std::string>(v) << std::endl;

    // 3. std::function (general-purpose polymorphic function wrapper)
    std::function<int(int)> f;
    f = [](int x) { return ++x; };
    f = [](int x) { return --x; };
    std::cout << f(100) << std::endl;

    return 0;
}