// Practical 12: Library Management System
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class LibraryException : public std::exception {
public:
    explicit LibraryException(const std::string& message) : message_(message) {}
    const char* what() const throw() { return message_.c_str(); }

private:
    std::string message_;
};

class LibraryItem {
protected:
    int id_;
    std::string title_;
    std::string author_;

public:
    LibraryItem(int id, const std::string& title, const std::string& author)
        : id_(id), title_(title), author_(author) {}

    virtual ~LibraryItem() {}
    virtual const char* typeName() const = 0;

    int id() const { return id_; }
    const std::string& title() const { return title_; }
    const std::string& author() const { return author_; }
};

class Book : public LibraryItem {
private:
    bool available_;

public:
    Book(int id, const std::string& title, const std::string& author,
         bool available)
        : LibraryItem(id, title, author), available_(available) {}

    const char* typeName() const { return "Book"; }

    bool available() const { return available_; }
    void issue() {
        if (!available_)
            throw LibraryException("The book is already issued.");
        available_ = false;
    }
    void returnBook() {
        if (available_)
            throw LibraryException("The book is already available.");
        available_ = true;
    }
};

class Library {
private:
    std::vector<std::unique_ptr<LibraryItem> > items_;
    std::string fileName_;

    Book* findBook(int id) {
        for (size_t i = 0; i < items_.size(); ++i) {
            if (items_[i]->id() == id)
                return dynamic_cast<Book*>(items_[i].get());
        }
        return 0;
    }

    static std::string csvField(const std::string& value) {
        if (value.find(',') == std::string::npos &&
            value.find('"') == std::string::npos)
            return value;

        std::string escaped;
        escaped.push_back('"');
        for (size_t i = 0; i < value.size(); ++i) {
            if (value[i] == '"')
                escaped += "\"\"";
            else
                escaped.push_back(value[i]);
        }
        escaped.push_back('"');
        return escaped;
    }

    static std::vector<std::string> splitCsv(const std::string& line) {
        std::vector<std::string> fields;
        std::string field;
        bool quoted = false;

        for (size_t i = 0; i < line.size(); ++i) {
            char ch = line[i];
            if (ch == '"' && quoted && i + 1 < line.size() && line[i + 1] == '"') {
                field.push_back('"');
                ++i;
            } else if (ch == '"') {
                quoted = !quoted;
            } else if (ch == ',' && !quoted) {
                fields.push_back(field);
                field.clear();
            } else {
                field.push_back(ch);
            }
        }
        fields.push_back(field);
        return fields;
    }

public:
    explicit Library(const std::string& fileName) : fileName_(fileName) {}

    void load() {
        std::ifstream input(fileName_.c_str());
        if (!input)
            return;

        std::string line;
        std::getline(input, line);

        int count = 0;
        while (std::getline(input, line)) {
            if (line.empty())
                continue;

            try {
                std::vector<std::string> fields = splitCsv(line);
                if (fields.size() != 4)
                    throw LibraryException("Malformed CSV record.");

                int id = std::stoi(fields[0]);
                bool available = fields[3] == "1";
                if (findBook(id) != 0)
                    throw LibraryException("Duplicate book ID found.");

                items_.push_back(std::unique_ptr<LibraryItem>(
                    new Book(id, fields[1], fields[2], available)));
                ++count;
            } catch (const std::exception& error) {
                std::cout << "Skipped invalid record: " << error.what() << '\n';
            }
        }

        std::cout << "Loaded " << count << " book(s).\n";
    }

    void save() const {
        std::ofstream output(fileName_.c_str(), std::ios::trunc);
        if (!output)
            throw LibraryException("Unable to open the data file for writing.");

        output << "id,title,author,available\n";
        for (size_t i = 0; i < items_.size(); ++i) {
            Book* book = dynamic_cast<Book*>(items_[i].get());
            if (book == 0)
                continue;

            output << book->id() << ','
                   << csvField(book->title()) << ','
                   << csvField(book->author()) << ','
                   << (book->available() ? "1" : "0") << '\n';
        }
        if (!output)
            throw LibraryException("Error occurred while writing the data file.");
    }

    void addBook(int id, const std::string& title,
                 const std::string& author) {
        if (id <= 0)
            throw LibraryException("Book ID must be a positive number.");
        if (title.empty() || author.empty())
            throw LibraryException("Title and author cannot be empty.");
        if (findBook(id) != 0)
            throw LibraryException("A book with this ID already exists.");

        items_.push_back(std::unique_ptr<LibraryItem>(
            new Book(id, title, author, true)));
        std::cout << "Book added successfully.\n";
    }

    void listBooks() const {
        if (items_.empty()) {
            std::cout << "No books are stored.\n";
            return;
        }

        std::cout << "\nID\tTitle\t\tAuthor\t\tStatus\n";
        for (size_t i = 0; i < items_.size(); ++i) {
            const Book* book =
                dynamic_cast<const Book*>(items_[i].get());
            if (book != 0) {
                std::cout << book->id() << '\t'
                          << book->title() << "\t\t"
                          << book->author() << "\t\t"
                          << (book->available() ? "Available" : "Issued")
                          << '\n';
            }
        }
    }

    void searchBooks(const std::string& keyword) const {
        bool found = false;
        for (size_t i = 0; i < items_.size(); ++i) {
            const Book* book =
                dynamic_cast<const Book*>(items_[i].get());
            if (book != 0) {
                if (book->title().find(keyword) != std::string::npos ||
                    book->author().find(keyword) != std::string::npos ||
                    std::to_string(book->id()).find(keyword) != std::string::npos) {
                    std::cout << "ID: " << book->id()
                              << ", Title: " << book->title()
                              << ", Author: " << book->author()
                              << ", Status: "
                              << (book->available() ? "Available" : "Issued")
                              << '\n';
                    found = true;
                }
            }
        }
        if (!found)
            std::cout << "No matching book found.\n";
    }

    void issueBook(int id) {
        Book* book = findBook(id);
        if (book == 0)
            throw LibraryException("Book ID not found.");
        book->issue();
        std::cout << "Book issued successfully.\n";
    }

    void returnBook(int id) {
        Book* book = findBook(id);
        if (book == 0)
            throw LibraryException("Book ID not found.");
        book->returnBook();
        std::cout << "Book returned successfully.\n";
    }
};

int readPositiveId() {
    int id;
    std::cin >> id;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw LibraryException("Please enter a valid numeric ID.");
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return id;
}

int main() {
    Library library("books.csv");

    try {
        library.load();
    } catch (const std::exception& error) {
        std::cout << "File error: " << error.what() << '\n';
    }

    int choice = 0;
    while (choice != 6) {
        std::cout << "\n=== Library Management System ===\n"
                  << "1. Add book\n"
                  << "2. Search book\n"
                  << "3. List books\n"
                  << "4. Issue book\n"
                  << "5. Return book\n"
                  << "6. Save and exit\n"
                  << "Choice: ";

        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid menu choice.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            if (choice == 1) {
                std::cout << "Book ID: ";
                int id = readPositiveId();
                std::cout << "Title: ";
                std::string title;
                std::getline(std::cin, title);
                std::cout << "Author: ";
                std::string author;
                std::getline(std::cin, author);
                library.addBook(id, title, author);
            } else if (choice == 2) {
                std::cout << "Enter title, author or ID: ";
                std::string keyword;
                std::getline(std::cin, keyword);
                library.searchBooks(keyword);
            } else if (choice == 3) {
                library.listBooks();
            } else if (choice == 4) {
                std::cout << "Book ID to issue: ";
                library.issueBook(readPositiveId());
            } else if (choice == 5) {
                std::cout << "Book ID to return: ";
                library.returnBook(readPositiveId());
            } else if (choice != 6) {
                std::cout << "Invalid menu choice.\n";
            }
        } catch (const LibraryException& error) {
            std::cout << "Error: " << error.what() << '\n';
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }

    try {
        library.save();
        std::cout << "Data saved to books.csv. Goodbye!\n";
    } catch (const LibraryException& error) {
        std::cout << "Save error: " << error.what() << '\n';
    }

    return 0;
}
