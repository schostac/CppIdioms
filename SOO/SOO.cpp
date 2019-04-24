#include <iostream>
#include <cstring>

/*
 * Small object optimization
 * It's used to avoid heap (i.e. dynamic memory allocation)
 * for small objects that are instead stored in
 * a small buffer on stack. For example, std::string 
 * or boost::small_vector
 * https://www.boost.org/doc/libs/1_70_0/doc/html/boost/container/small_vector.html
 */

class MyString {
    static constexpr int smallObjectSize = 16;
    size_t _size;
    union Data {
        char buf[smallObjectSize]; // for small object
        char *ptr;
    } _data;
 
public:
    explicit MyString(const char* str): _size(std::strlen(str)) { 
        if(_size > smallObjectSize) {
            _data.ptr = new char[_size]; 
            std::strcpy(_data.ptr, str);
        }
        else std::strcpy(_data.buf, str);
        // Note: we use placement new operator for small objects
        // of user-defined class
    }
    ~MyString() {
        if (_size > smallObjectSize) delete[] _data.ptr;
    }
    MyString(MyString && other): _size(other._size) {
        if(other._size > smallObjectSize)  {
            _data.ptr = other._data.ptr;
            other._data.ptr = nullptr;
            other._size = 0;
        } else std::strcpy(_data.buf, other._data.buf);
    }
    char* data() {
        return (_size > smallObjectSize) ? _data.ptr : _data.buf;
    }
    size_t size() const { return _size; }
};

int main()
{
    MyString str1("Short text");
    auto str2 = std::move(str1);
    std::cout << str2.data() << std::endl;

    MyString str3("Loooooooooooooooooooooooooooooooooooooooooooooooooonger text");
    auto str4 = std::move(str3);
    std::cout << str4.data() << std::endl;

    return 0;
}

