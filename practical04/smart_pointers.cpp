// Practical 04: RAII and Smart Pointers
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Document {
public:
    explicit Document(std::string title) : title_(std::move(title)) {
        std::cout << "Created: " << title_ << '\n';
    }

    ~Document() {
        std::cout << "Destroyed: " << title_ << '\n';
    }

    void read() const {
        std::cout << "Reading " << title_ << '\n';
    }

private:
    std::string title_;
};

int main() {
    std::cout << "unique_ptr: one owner\n";
    {
        std::unique_ptr<Document> document(
            new Document("Private notes"));
        document->read();
    }

    std::cout << "\nshared_ptr: shared ownership\n";
    {
        std::shared_ptr<Document> firstOwner(
            new Document("Team report"));
        auto secondOwner = firstOwner;
        std::cout << "Owners while both exist: " << firstOwner.use_count() << '\n';
        secondOwner->read();
    }

    std::cout << "\nAll objects were released automatically by RAII.\n";
    return 0;
}
