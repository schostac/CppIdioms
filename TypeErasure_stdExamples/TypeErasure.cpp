#include <iostream>
#include <algorithm>
#include <functional>
#include <variant> 
#include <vector>
#include <memory>
#include <cstdlib>
#include <any>

/*
 * Type erasure (examples from std)
 */

struct Subtruct {
    int operator()(int x) const { return --x; }
};

struct Add {
    int operator()(int x) const { return ++x; }
};

struct Point {
    int x, y;
};

int main()
{
    // 1. std::any (type-safe container for single values of any type)
    std::any a = 100;
    std::cout << std::any_cast<int>(a) << '\n';
    a = Point{15,15};

    // 2. std::variant (type-safe union)

    std::variant<int, std::string> v;
    v = 12;
    std::cout << std::get<int>(v) << '\n';
    v = std::string{"text"};

    std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>)
                std::cout << "int with value " << arg << '\n';
            else if constexpr (std::is_same_v<T, std::string>)
                std::cout << "std::string with value " << arg << '\n';
    }, v);

    // 3. std::function (general-purpose polymorphic function wrapper)
    std::function<int(const int)> f = [](int x){ return ++x; };
    f = Add{};
    f = Subtruct{};
    f(100);
    

    return 0;
}