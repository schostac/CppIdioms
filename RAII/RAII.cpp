#include <iostream>
#include <utility>
#include <memory>

/*
 * Resource Acquisition Is Initialization (RAII)
 * 
 * It is used to guarantee release of resource at 
 * the end of a scope / destruction. 
 * It thus ensures no resource leaks and
 * provides basic exception safety guarantee.
 * 
 * It binds the life cycle of a resource that 
 * must be acquired before use to the lifetime 
 * of an object.
 * 
 * Resource could be allocated heap memory, thread of execution, 
 * open socket, open file, locked mutex, disk space, database 
 * connection, id or anything else that exists in limited supply.
 * 
 * Examples from C++ Standard Library include std::unique_ptr,
 * std::ofstream, std::lock_guard, etc.
 * 
 * So, in order to implement RAII:
 * - wrap resource into a class;
 * - resource is acquired in constructor of the class
 *   immediately after its allocation;
 * - resource is automatically released in destructor of the class;
 * - resource is used via interface of the class;
 * 
 * Usually, only one instance of the class owns particular resource
 * (std::unqiue_ptr), but sometimes ownership can also be shared 
 * (std::shared_ptr) as long as resource is properly released.
 * 
 * Idially, RAII wrapper should own and manage only one resource.
 */

template<typename T>
class UniquePointer {
public:
    UniquePointer():ptr{nullptr} {}
    UniquePointer(T *ptr_):ptr{ptr_} {}

    template<typename... Args>
    UniquePointer(Args&&... args)
        : ptr(new T(std::forward<Args>(args)...)) {}

    ~UniquePointer() { delete ptr; }

    UniquePointer(const UniquePointer&) = delete;
    UniquePointer(UniquePointer && other)noexcept: ptr{other.ptr} {
        other.ptr = nullptr;
    }

    UniquePointer& operator=(const UniquePointer&) = delete;
    UniquePointer& operator=(UniquePointer && other) noexcept {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    };


    T* get() { return ptr; }
    void reset() { delete ptr; ptr = nullptr; }
    T* release() {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }
    T& operator*() { return *ptr; }
    operator bool() { return ptr != nullptr; }

private:
    T *ptr;
};

class Point 
{
public:
    Point(const int x_, const int y_): x{x_}, y{y_} {}
private:
    int x, y;
};

int main()
{
    auto p1 = UniquePointer<Point>(5, 10);
    std::cout << std::boolalpha << ((bool)p1) << std::endl;
    auto p2 = std::move(p1);
    std::cout << ((bool)p1) << std::endl;
    std::cout << ((bool)p2) << std::endl;
    return 0;
}