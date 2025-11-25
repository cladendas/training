#include <string>

struct Address {
    unsigned num;
    std::string name;
};

//композиция
class Student{
public:
    std::string name;
    Address address;
};

class Shape {
public:
    ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};

//наследование
class Circle: public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return M_PI * radius * radius;
    }

    double perimeter() const override {
        return 2 * M_PI * radius;
    }
};