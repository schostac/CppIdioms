#include <iostream>

/*
 * Curiously recurring template pattern (CRTP) or static polymorphism
 * (example with relational operators).
 */

template<class Derived>
struct Comparing {};

template <class Derived>
bool operator==(const Comparing<Derived> &lhs, const Comparing<Derived> &rhs) {
    const auto & dlhs = static_cast<const Derived&>(lhs);
    const auto & drhs = static_cast<const Derived&>(rhs);
    return !(dlhs < drhs) and !(drhs < dlhs);
}

template <class Derived>
bool operator!=(const Comparing<Derived> &lhs, const Comparing<Derived> &rhs) {
    return !(lhs == rhs);
}

template <class Derived>
bool operator>(const Comparing<Derived> &lhs, const Comparing<Derived> &rhs) {
    const auto & dlhs = static_cast<const Derived&>(lhs);
    const auto & drhs = static_cast<const Derived&>(rhs);
    return (drhs < dlhs);
}

template <class Derived>
bool operator>=(const Comparing<Derived> &lhs, const Comparing<Derived> &rhs) {
    const auto & dlhs = static_cast<const Derived&>(lhs);
    const auto & drhs = static_cast<const Derived&>(rhs);
    return (drhs < dlhs) or (drhs == dlhs);
}

template <class Derived>
bool operator<=(const Comparing<Derived> &lhs, const Comparing<Derived> &rhs) {
    const auto & dlhs = static_cast<const Derived&>(lhs);
    const auto & drhs = static_cast<const Derived&>(rhs);
    return (dlhs < drhs) or (drhs == dlhs);
}

class Data : public Comparing<Data> 
{
public:
    explicit Data(const int x_): x(x_) {}
    friend bool operator<(const Data&, const Data &);
private:
    int x;
};

bool operator<(const Data &lhs, const Data &rhs) {
    return lhs.x < rhs.x;
}

int main()
{   
    Data d1{5}, d2{10};

    std::cout << std::boolalpha;

    std::cout << "d1 < d2: " << (d1 < d2) << '\n';
    std::cout << "d1 == d2: " << (d1 == d2) << '\n';
    std::cout << "d1 != d2: " << (d1 != d2) << '\n';
    std::cout << "d1 > d2: " << (d1 > d2) << '\n';
    std::cout << "d1 >= d2: " << (d1 >= d2) << '\n';
    std::cout << "d1 <= d2: " << (d1 <= d2) << '\n';

    Data d3{20}, d4{20};

    std::cout << "d3 < d4: " << (d3 < d4) << '\n';
    std::cout << "d3 > d4: " << (d3 > d4) << '\n';
    std::cout << "d3 <= d4: " << (d3 <= d4) << '\n';
    std::cout << "d3 == d4: " << (d3 == d4) << '\n';
    std::cout << "d3 != d4: " << (d3 != d4) << '\n';
    std::cout << "d3 >= d4: " << (d3 >= d4) << std::endl;

    return 0;
}
