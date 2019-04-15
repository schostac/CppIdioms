#include <iostream>
#include <stdexcept>
#include <numeric>
#include <vector>
#include <set>

/*
 * Return Type Resolver 
 * Used to deduce the type of the variable being initialized or assigned to.
 * Relies on templatized conversion operator (function) of a proxy class. 
 */

class Range {
    const size_t from, to;
public:
    Range(const size_t from, const size_t to): from(from), to(to) {
        if(from > to) throw std::logic_error{""};
    }

    template<typename SequenceContainer>
    operator SequenceContainer()
    {
        SequenceContainer container;
        for(size_t i = from; i < to; ++i)
            container.insert(container.end(), i);
        return container;
    }
};

class String {
    const std::string & s;
public:
    String(const std::string & s): s(s) {}
    operator int() { return std::stoi(s); }
    operator double() { return std::stod(s); }
};


int main()
{
    std::set<int> r = Range(0, 3);
    for(auto i : r)
        std::cout << i << std::endl;

    std::string s = "125";
    int x = String(s);
    double y = String("3.14");
    std::cout << x << " " << y << std::endl;

    return 0;
}
