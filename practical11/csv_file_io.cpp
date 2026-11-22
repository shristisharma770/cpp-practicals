// Practical 11: CSV Student Records and File Positions
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct Student {
    int id;
    std::string name;
    double marks;
};

int main() {
    const std::string csvFile = "students.csv";
    {
        std::ofstream output(csvFile);
        if (!output) throw std::runtime_error("Unable to open students.csv for writing.");
        output << "id,name,marks\n"
               << "101,Aarav Patil,87.5\n"
               << "102,Meera Kulkarni,91.0\n"
               << "103,Riya Shah,78.5\n";
        if (!output) throw std::runtime_error("CSV writing failed.");
        std::cout << "tellp() after writing: " << output.tellp() << '\n';
    }

    std::ifstream input(csvFile);
    if (!input) throw std::runtime_error("Unable to open students.csv for reading.");

    std::string line;
    std::getline(input, line);  // header
    std::vector<Student> students;
    while (std::getline(input, line)) {
        std::stringstream row(line);
        std::string id, name, marks;
        if (!std::getline(row, id, ',') || !std::getline(row, name, ',') ||
            !std::getline(row, marks)) {
            std::cerr << "Skipping malformed row: " << line << '\n';
            continue;
        }
        try {
            students.push_back({std::stoi(id), name, std::stod(marks)});
        } catch (const std::exception&) {
            std::cerr << "Skipping invalid row: " << line << '\n';
        }
    }
    std::cout << "tellg() at end: " << input.tellg() << '\n';
    input.clear();
    input.seekg(0);
    std::cout << "seekg(0), tellg(): " << input.tellg() << '\n';

    std::cout << "\nStudent records:\n";
    std::cout << std::fixed << std::setprecision(1);
    for (const Student& student : students) {
        std::cout << student.id << " | " << student.name << " | "
                  << student.marks << '\n';
    }

    std::fstream positions("file_positions.txt",
                           std::ios::in | std::ios::out | std::ios::trunc);
    if (!positions) throw std::runtime_error("Unable to open position demo file.");
    positions << "ABCDE";
    std::cout << "\nput position after write (tellp): " << positions.tellp() << '\n';
    positions.seekp(2);
    positions << 'X';
    std::cout << "put position after seekp(2): " << positions.tellp() << '\n';
    positions.flush();
    positions.seekg(0);
    std::cout << "get position after seekg(0): " << positions.tellg() << '\n';
    char first;
    positions.get(first);
    std::cout << "First character after get(): " << first
              << ", tellg(): " << positions.tellg() << '\n';
    return 0;
}
