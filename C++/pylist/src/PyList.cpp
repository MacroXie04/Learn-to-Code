#include "PyList.h"

using namespace std;

// deallocate memory
void PyList::releaseMemory() {
    for (int i = 0; i < count; i++) {
        if (types[i] == CHAR) {
            delete (char*)arr[i];
        }
        if (types[i] == BOOL) {
            delete (bool*)arr[i];
        }
        if (types[i] == INT) {
            delete (int*)arr[i];
        }
        if (types[i] == FLOAT) {
            delete (float*)arr[i];
        }
        if (types[i] == STRING) {
            delete (string*)arr[i];
        }
    }
    delete[] arr;
    delete[] types;
}

// copy elements and types over from other list to this one
void PyList::copyElementsFromOtherMemoryLocation(const PyList& other) {
    for (int i = 0; i < other.count; i++) {
        if (other.types[i] == CHAR) {
            arr[i] = new char(*(char*)other.arr[i]);
        }
        if (other.types[i] == BOOL) {
            arr[i] = new bool(*(bool*)other.arr[i]);
        }
        if (other.types[i] == INT) {
            arr[i] = new int(*(int*)other.arr[i]);
        }
        if (other.types[i] == FLOAT) {
            arr[i] = new float(*(float*)other.arr[i]);
        }
        if (other.types[i] == STRING) {
            arr[i] = new string(*(string*)other.arr[i]);
        }
        types[i] = other.types[i];
    }
}

// resize method
// allocate new memory location of double capacity
// transfer existing elements over and delete old memory location
void PyList::resize() {
    if (count == capacity) {
        capacity *= 2;
        // allocate new memory
        void** temp = new void*[capacity];
        Type* tempTypes = new Type[capacity];
        // copy existing elements
        for (int i = 0; i < count; i++) {
            if (types[i] == CHAR) {
                temp[i] = new char(*(char*)arr[i]);
            }
            if (types[i] == BOOL) {
                temp[i] = new bool(*(bool*)arr[i]);
            }
            if (types[i] == INT) {
                temp[i] = new int(*(int*)arr[i]);
            }
            if (types[i] == FLOAT) {
                temp[i] = new float(*(float*)arr[i]);
            }
            if (types[i] == STRING) {
                temp[i] = new string(*(string*)arr[i]);
            }
            tempTypes[i] = types[i];
        }
        // release old memory
        releaseMemory();
        // assign new pointers
        arr = temp;
        types = tempTypes;
    }
}

// default constructor
PyList::PyList() {
    count = 0;
    capacity = 1;
    arr = new void*[capacity];
    types = new Type[capacity];
}

// copy constructor
PyList::PyList(const PyList& other) {
    count = other.count;
    capacity = other.capacity;
    arr = new void*[capacity];
    types = new Type[capacity];
    copyElementsFromOtherMemoryLocation(other);
}

// overloaded assignment operator
PyList& PyList::operator=(const PyList& other) {
    if (this == &other) {
        return *this;
    }
    releaseMemory();
    count = other.count;
    capacity = other.capacity;
    arr = new void*[capacity];
    types = new Type[capacity];
    copyElementsFromOtherMemoryLocation(other);
    return *this;
}

// overloaded left shift operator for output
std::ostream& operator<<(std::ostream& os, const PyList& list) {
    os << "[";
    for (int i = 0; i < list.count; i++) {
        if (list.types[i] == CHAR) {
            os << *(char*)list.arr[i];
        }
        if (list.types[i] == BOOL) {
            os << (*(bool*)list.arr[i] ? "true" : "false");
        }
        if (list.types[i] == INT) {
            os << *(int*)list.arr[i];
        }
        if (list.types[i] == FLOAT) {
            os << *(float*)list.arr[i];
        }
        if (list.types[i] == STRING) {
            os << *(string*)list.arr[i];
        }
        if (i < list.count - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

// destructor
PyList::~PyList() {
    releaseMemory();
}
