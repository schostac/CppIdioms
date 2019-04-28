#include <iostream>

/*
 * Empty base optimization (EBO)
 * 
 * The size of any object must be at least 1 byte even if 
 * the type is empty (no non-static data members).
 * It's needed so that the addresses of distinct objects 
 * of the same type are always distinct.
 * 
 * However, base class sub-objects are not required to have size
 * at least 1 byte, and can be completely optimized out. This is called
 * empty base optimization.
 * 
 * E.g. std::vector, std::function, std::shared_ptr, etc.
 * use EBO to avoid additional storage for allocator member.
 * Also, EBO is used in boost::compressed_pair:
 * https://www.boost.org/doc/libs/1_70_0/libs/utility/doc/html/compressed_pair.html
 * 
 * More at:
 * https://en.cppreference.com/w/cpp/language/ebo
 * https://stackoverflow.com/questions/4325144/when-do-programmers-use-empty-base-optimization-ebo
 */


int main()
{
    return 0;
}