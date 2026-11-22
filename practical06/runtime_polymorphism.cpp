// Practical 06: Runtime Polymorphism and Abstract Classes
#include <cmath>
#include <iomanip>
#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual const char* name() const = 0;
};

class Circle : public Shape {
public:
    explicit Circle(double radius) : radius_(radius) {}
    double area() const override { return 3.141592653589793 * radius_ * radius_; }
    const char* name() const override { return "Circle"; }

private:
    double radius_;
};

class Rectangle : public Shape {
public:
    Rectangle(double length, double width) : length_(length), width_(width) {}
    double area() const override { return length_ * width_; }
    const char* name() const override { return "Rectangle"; }

private:
    double length_;
    double width_;
};

class Triangle : public Shape {
public:
    Triangle(double base, double height) : base_(base), height_(height) {}
    double area() const override { return 0.5 * base_ * height_; }
    const char* name() const override { return "Triangle"; }

private:
    double base_;
    double height_;
};

int main() {
    Circle circle(3);
    Rectangle rectangle(4, 5);
    Triangle triangle(6, 2);

    Shape* shapes[] = { &circle, &rectangle, &triangle };

    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < 3; ++i) {
        std::cout << shapes[i]->name()
                  << " area = " << shapes[i]->area() << '\n';
    }
    return 0;
}
