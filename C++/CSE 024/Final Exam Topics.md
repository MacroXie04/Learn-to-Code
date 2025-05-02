# CSE 024 Final Exam Topics

## Overview
- C++ Review
- Data abstraction
- Encapsulation
- Access control
- Composition
- Pointers
- Dynamic Memory Allocation
- Overloaded Operators
- Inheritance
- Abstract Data Types

## C++ Review
- Variables, types, operators
- Input and output
- Conditionals
- Functions
- Loops
- Vectors
- File Streams
- Structures
- Bobcat UI Library

## Data Abstraction
- The process of focusing on what is important and ignoring what is irrelevant

```cpp
struct Person {
    string firstName;
    string lastName;
    string email;
    int grade;
};
```

## Encapsulation

- The process of bundling together data and methods into a single unit

```cpp
struct Rectangle {
    int width, height;

    Rectangle();
    void draw();
};
```

## Access Control
- A mechanism used to restrict how different parts of a program can access the data members and methods within a class

```cpp
class GroceryItem {
    string name;
    float price;
public:
    GroceryItem(string name, float price);
    string getName();
    float getPrice();
};
```


## Composition
- The design principle where one class contains objects of another class as member variables

```cpp
class Application: public bobcat::Application {
    bobcat::Window* window;
    Toolbar* toolbar;
    Canvas* canvas;
public:
    Application();
};
```

## Pointers
- Representation of computer memory
- C++ data types and their size in memory
- Getting the memory address of a variable
- Using pointers to store memory address of variables
- Dereferencing pointers
- Pointer arithmetic
- Manipulating data using pointers

## Dynamic Memory Allocation
- Differences between stack and heap memory
- Using pointers to allocate memory dynamically on the heap
- Dynamic memory allocation strategy
  - Start by allocating small chunk of memory on the heap, and resize when you run out of space

## Overloaded Operators
- Operator overloading allows us to define how operators behave for user-defined classes
  - Overloaded assignment operator: =
  - Overloaded subscript operator: [ ]
  - Overloaded insertion operator: <<
- Copy constructor

## Inheritance
- A mechanism where one class inherits properties/members from another class

```cpp
class Animal {
    ...
};

class Dog : public Animal {
public:
    Dog();
    void speak();
};
```


## Abstract Data Types
- Virtual methods
- Pure virtual methods
- Virtual destructor
- Abstract class

```cpp
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape(){};
};
```

