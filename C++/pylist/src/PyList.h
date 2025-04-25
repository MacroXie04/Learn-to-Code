#ifndef PY_LIST_H
#define PY_LIST_H

#include <iostream>
#include <string>
#include <type_traits>

enum Type { CHAR, BOOL, INT, FLOAT, STRING };

class PyList {
    int count;
    int capacity;
    void** arr;
    Type* types;

    void releaseMemory();
    void copyElementsFromOtherMemoryLocation(const PyList& other);
    void resize();

public:
    PyList();
    PyList(const PyList& other);
    
    template <typename T>
    void append(T x) {
        if constexpr (std::is_same<T, char>::value) {
            arr[count] = new char(x);
            types[count] = CHAR;
        } else if constexpr (std::is_same<T, bool>::value) {
            arr[count] = new bool(x);
            types[count] = BOOL;
        } else if constexpr (std::is_same<T, int>::value) {
            arr[count] = new int(x);
            types[count] = INT;
        } else if constexpr (std::is_same<T, float>::value) {
            arr[count] = new float(x);
            types[count] = FLOAT;
        } else if constexpr (std::is_same<T, std::string>::value) {
            arr[count] = new std::string(x);
            types[count] = STRING;
        } else {
            static_assert(sizeof(T) == 0, "Unsupported type");
        }
        count++;
        resize();
    }

    PyList& operator=(const PyList& other);
    friend std::ostream& operator<<(std::ostream& os, const PyList& list);
    ~PyList();
};

#endif
