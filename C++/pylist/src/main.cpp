#include <iostream>
#include "PyList.h"
using namespace std;

int main() {

    PyList list1;
    list1.append('A');
    list1.append(true);
    list1.append(5.75f);
    list1.append(string("California"));

    PyList list2 = list1;
    list1.append(7);

    cout << "List 1: " << list1 << endl;
    cout << "List 2: " << list2 << endl;

    return 0;
}