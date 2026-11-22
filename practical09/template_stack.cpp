// Practical 09: Generic Stack Using Templates
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class Stack {
public:
    void push(const T& value) { values_.push_back(value); }

    T pop() {
        if (values_.empty()) throw std::out_of_range("Cannot pop an empty stack");
        T value = values_.back();
        values_.pop_back();
        return value;
    }

    bool empty() const { return values_.empty(); }

private:
    std::vector<T> values_;
};

template <typename T>
void demonstrate(const std::string& label, const T& first, const T& second) {
    Stack<T> stack;
    stack.push(first);
    stack.push(second);
    std::cout << label << ": " << stack.pop() << ", " << stack.pop() << '\n';
    try {
        stack.pop();
    } catch (const std::out_of_range& error) {
        std::cout << "Empty-stack test: " << error.what() << '\n';
    }
}

int main() {
    demonstrate<int>("int", 10, 20);
    demonstrate<float>("float", 1.5f, 2.5f);
    demonstrate<std::string>("string", "first", "second");
    return 0;
}
