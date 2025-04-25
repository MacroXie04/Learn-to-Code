
---

# **Midterm Exam**

> The following `Circle` class will be used for questions 1 - 10. Assume that all constructors and member methods are implemented correctly.

```cpp
#include <cmath>

class Circle {
    float x, y, radius;
    float area;

public:
    float r, g, b;

    Circle();
    Circle(float x, float y, float radius);
    Circle(float x, float y, float radius, float r, float g, float b);

    void draw() const;
};
```

---

### **1. Which statement best describes the following code snippet?**
```cpp
Circle c;
```
- **A.** A circle object is created on the stack.  
- **B.** A circle object is created on the heap.  
- **C.** A circle object is not created, `c` is just a `Circle` pointer.  
- **D.** The code snippet results in a compilation error.  

---

### **2. Which statement best describes the following code snippet?**
```cpp
Circle* c;
```
- **A.** A circle object is created on the stack.  
- **B.** A circle object is created on the heap.  
- **C.** A circle object is not created, `c` is just a `Circle` pointer.  
- **D.** The code snippet results in a compilation error.  

---

### **3. Which statement best describes the following code snippet?**
```cpp
Circle* c = new Circle();
```
- **A.** A circle object is created on the stack.  
- **B.** A circle object is created on the heap.  
- **C.** A circle object is not created, `c` is just a `Circle` pointer.  
- **D.** The code snippet results in a compilation error.  

---

### **4. Which statement best describes the following code snippet?**
```cpp
Circle* c = new Circle(0.5, 0.5);
```
- **A.** A circle object is created on the stack.  
- **B.** A circle object is created on the heap.  
- **C.** A circle object is not created, `c` is just a `Circle` pointer.  
- **D.** The code snippet results in a compilation error.  

---

### **5. Suppose you have a `std::vector<Circle*> circles` with some arbitrary number of circles. Which code snippet correctly renders the entire collection?**

- **A.** `circles->draw();`  
- **B.** `circles.draw();`  
- **C.**  
  ```cpp
  for (unsigned int i = 0; i < 10; i++) {
      circles[i]->draw();
  }
  ```
- **D.**  
  ```cpp
  for (unsigned int i = 0; i < circles.size(); i++) {
      circles[i]->draw();
  }
  ```

---

### **6. Suppose you have a `std::vector<Circle*> circles` with some arbitrary number of circles. Which code snippet correctly erases all items from the collection?**

- **A.** `delete circles;`  
- **B.** `circles.clear();`  
- **C.**  
  ```cpp
  for (unsigned int i = 0; i < circles.size(); i++) {
      delete circles[i];
  }
  delete circles;
  ```
- **D.**  
  ```cpp
  for (unsigned int i = 0; i < circles.size(); i++) {
      delete circles[i];
  }
  circles.clear();
  ```

---

### **7. How many data members, excluding methods and constructors, are accessible from outside of the `Circle` class?**

- **A.** 1  
- **B.** 2  
- **C.** 3  
- **D.** 4  

---

### **8. Which members are not accessible from outside of the `Circle` class?**

- **A.** `r`, `g`, and `b`  
- **B.** `x`, `y`, `radius`, and `area`  
- **C.** `r`, `g`, `b`, and `draw`  
- **D.** `x`, `y`, `radius`, `area`, `r`, `g`, `b`, and `draw`  

---

### **9. Which code snippet implements a member method that allows read-only access to the color of a `Circle`?**  
Assume your `Circle` class has access to the following structure:

```cpp
struct Color {
    float r, g, b;
    Color(float r, float g, float b);
};
```

- **A.**  
  ```cpp
  float Circle::getColor() const {
      return r, g, b;
  }
  ```
- **B.**  
  ```cpp
  float float float Circle::getColor() const {
      return r, g, b;
  }
  ```
- **C.**  
  ```cpp
  Color Circle::getColor() const {
      return Color(r, g, b);
  }
  ```
- **D.**  
  ```cpp
  Color Circle::getColor() const {
      return Color();
  }
  ```

---

### **10. Which code snippet implements a member method to update the size of the `Circle`, ensuring that variables dependent on the size are also updated?**

- **A.**  
  ```cpp
  void Circle::setSize(float radius) {
      this->radius = radius;
  }
  ```
- **B.**  
  ```cpp
  void Circle::setSize(float radius) {
      this->radius = radius;
      area = M_PI * radius * radius;
  }
  ```
- **C.**  
  ```cpp
  void Circle::setSize(float size) {
      this->size = size;
  }
  ```
- **D.**  
  ```cpp
  void Circle::setSize(float size) {
      this->size = size;
      area = M_PI * radius * radius;
  }
  ```

---

I'll now extract and convert the text from the images into a readable format. Please hold on while I process them.

Here is the extracted text from the images in a readable format:

---

### **Color, Square, and Canvas Classes**
The following three classes, **Color, Square, and Canvas**, will be used for questions 11-20. The drawing in **Figure 1** represents how a `Square` object should be rendered from its data members.

#### **Color.h**
```cpp
class Color {
    float r, g, b;
  
public:
    Color(float r, float g, float b);

    float getR() const;
    float getG() const;
    float getB() const;
};
```

#### **Square.h**
```cpp
#include "Color.h"

class Square {
    float x, y, size;
    Color* color;

public:
    Square();
    Square(float x, float y, float size, Color color);

    void draw();
};
```

#### **Canvas.h**
```cpp
#include "Square.h"

class Canvas : public bobcat::Canvas_ {
    std::vector<Square*> squares;

public:
    Canvas(int x, int y, int w, int h);

    void addSquare(float x, float y, float size, Color color);
    void undo();
    void render();
    int getSquaresCount() const;
};
```

---
### **Question 11**  
**Which code snippet correctly implements the default constructor for `Square`?**  
The default square should create a **red square** of width and height equal to **0.5**, positioned at **(0.0, 0.0)**.

#### **Options**
A. 
```cpp
Square::Square() {
    x = 0.0;
    y = 0.0;
    size = 0.5;
    color = Color(1.0, 0.0, 0.0);
}
```
B. 
```cpp
Square::Square() {
    x = 0.0;
    y = 0.0;
    size = 0.5;
    color = new Color(1.0, 0.0, 0.0);
}
```
C. 
```cpp
Square::Square() {
    x = 0.0;
    y = 0.0;
    size = 0.5;
    color.r = 1.0;
    color.g = 0.0;
    color.b = 0.0;
}
```
D. 
```cpp
Square::Square() {
    x = 0.0;
    y = 0.0;
    size = 0.5;
    color->r = 1.0;
    color->g = 0.0;
    color->b = 0.0;
}
```

---
### **Question 12**  
**Which code snippet correctly implements the parameterized constructor for `Square`?**

#### **Options**
A. 
```cpp
Square::Square(float x, float y, float size, Color color) {
    this->x = x;
    this->y = y;
    this->size = size;
    color = color;
}
```
B. 
```cpp
Square::Square(float x, float y, float size, Color color) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->color = color;
}
```
C. 
```cpp
Square::Square(float x, float y, float size, Color color) {
    this->x = x;
    this->y = y;
    this->size = size;
    color->r = color.getR();
    color->g = color.getG();
    color->b = color.getB();
}
```
D. 
```cpp
Square::Square(float x, float y, float size, Color color) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->color = new Color(color.getR(), color.getG(), color.getB());
}
```

---
### **Question 13**  
**Which code snippet correctly implements the `addSquare` method for `Canvas`?**

#### **Options**
A. 
```cpp
void Canvas::addSquare(float x, float y, float size, Color color) {
    squares.push_back(new Square(x, y, size, color));
}
```
B. 
```cpp
void Canvas::addSquare(float x, float y, float size, Color color) {
    float r = color.r;
    float g = color.g;
    float b = color.b;
    squares.push_back(new Square(x, y, size, r, g, b));
}
```
C. 
```cpp
void Canvas::addSquare(float x, float y, float size, Color color) {
    float r = color.getR();
    float g = color.getG();
    float b = color.getB();
    squares.push_back(new Square(x, y, size, r, g, b));
}
```
D. 
```cpp
void Canvas::addSquare(float x, float y, float size, Color color) {
    float r = color->getR();
    float g = color->getG();
    float b = color->getB();
    squares.push_back(new Square(x, y, size, r, g, b));
}
```

---
### **Question 14**  
**Which code snippet correctly implements the `undo` method for `Canvas`?**  
The undo method should remove the last square that was drawn.

#### **Options**
A. 
```cpp
squares.pop_back();
```
B. 
```cpp
delete squares[squares.size() - 1];
```
C. 
```cpp
if (!squares.empty()) {
    delete squares[squares.size() - 1];
    squares.pop_back();
}
```
D. 
```cpp
if (!squares.empty()) {
    squares.pop_back();
    delete squares[squares.size() - 1];
}
```

---
### **Question 15**  
**Which code snippet correctly implements the `render` method for `Canvas`?**

#### **Options**
A. 
```cpp
void Canvas::render() {
    squares->draw();
}
```
B. 
```cpp
void Canvas::render() {
    squares.draw();
}
```
C. 
```cpp
void Canvas::render() {
    for (unsigned int i = 0; i < squares.size(); i++) {
        squares[i]->draw();
    }
}
```
D. 
```cpp
void Canvas::render() {
    for (unsigned int i = 0; i < squares.size(); i++) {
        squares[i].draw();
    }
}
```

---
### **Question 16**  
**Suppose you have a `Canvas* canvas` initialized correctly, which code snippet correctly adds a square to the canvas?**

#### **Options**
A. 
```cpp
canvas->squares.push_back(new Square());
```
B. 
```cpp
Color color = Color();
canvas->addSquare(0.0, 0.0, 0.2, color);
```
C. 
```cpp
Color color = Color(0.0, 0.0, 0.0);
canvas->addSquare(0.0, 0.0, 0.2, color);
```
D. 
```cpp
canvas->addSquare(0.0, 0.0, 0.2, 0.0, 0.0, 0.0);
```

---
### **Question 17**  
**Which statement is true about the following code snippet?**
```cpp
Canvas* canvas = new Canvas(100, 100, 300, 300);
Color color = Color(0.0, 0.0, 1.0);
canvas->addSquare(0.0, 0.0, 0.2, color);
canvas->render();
```

#### **Options**
A. The code snippet will add a **blue square** of size **0.2**, positioned at **(0.0, 0.0)**.  
B. The code snippet results in a **compilation error**.  
C. The code snippet results in a **runtime error**.  
D. None of the above.

---
### **Question 18**  
**Suppose you have a `Canvas* canvas` initialized correctly with some arbitrary number of squares, which statement is true about the following code snippet?**
```cpp
canvas->undo();
cout << "Number of Squares: " << canvas->getSquaresCount() << endl;
```

#### **Options**
A. The output would be `"Number of Squares: 0"`.  
B. Impossible to determine the number of squares from the information provided.  
C. The code snippet results in a **compilation error**.  
D. The code snippet results in a **runtime error**.

---

This is the fully extracted text from the images. Let me know if you need anything else! 🚀