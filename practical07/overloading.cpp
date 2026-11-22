// Practical 07: Compile-Time Polymorphism - Function and Operator Overloading
#include <iostream>

int add(int first, int second) {
    return first + second;
}

double add(double first, double second) {
    return first + second;
}

class ComplexNumber {
public:
    ComplexNumber(double real, double imaginary)
        : real_(real), imaginary_(imaginary) {}

    ComplexNumber operator+(const ComplexNumber& other) const {
        return ComplexNumber(real_ + other.real_, imaginary_ + other.imaginary_);
    }

    void display() const {
        std::cout << real_ << (imaginary_ < 0 ? " - " : " + ")
                  << (imaginary_ < 0 ? -imaginary_ : imaginary_) << "i";
    }

private:
    double real_;
    double imaginary_;
};

int main() {
    std::cout << "add(int, int): " << add(4, 6) << '\n';
    std::cout << "add(double, double): " << add(2.5, 1.75) << "\n\n";

    ComplexNumber first(3, 4);
    ComplexNumber second(2, -1);
    ComplexNumber sum = first + second;
    std::cout << "First: ";
    first.display();
    std::cout << "\nSecond: ";
    second.display();
    std::cout << "\nSum (operator+): ";
    sum.display();
    std::cout << '\n';
    return 0;
}
