// Practical 05: Single and Multilevel Inheritance
#include <iostream>
#include <string>
using namespace std;

class Person
{
protected:
    string name;
    int age;

public:
    Person(string personName, int personAge)
    {
        name = personName;
        age = personAge;
    }

    void displayPerson()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
    }
};

class Student : public Person
{
protected:
    int studentId;
    string course;

public:
    Student(string personName, int personAge, int id, string studentCourse)
        : Person(personName, personAge)
    {
        studentId = id;
        course = studentCourse;
    }

    void displayStudent()
    {
        displayPerson();
        cout << "Student ID: " << studentId << endl;
        cout << "Course: " << course << endl;
    }
};

class GraduateStudent : public Student
{
private:
    string researchTopic;
    string supervisor;

public:
    GraduateStudent(string personName, int personAge, int id,
                    string studentCourse, string topic, string guide)
        : Student(personName, personAge, id, studentCourse)
    {
        researchTopic = topic;
        supervisor = guide;
    }

    void displayGraduateStudent()
    {
        displayStudent();
        cout << "Research Topic: " << researchTopic << endl;
        cout << "Supervisor: " << supervisor << endl;
    }
};

int main()
{
    cout << "=== Single Inheritance: Person -> Student ===" << endl;

    Student student("Aarav Patil", 20, 101, "Computer Science");
    student.displayStudent();

    cout << "\n=== Multilevel Inheritance: Person -> Student -> GraduateStudent ==="
         << endl;

    GraduateStudent graduate("Meera Kulkarni", 24, 201, "MCA",
                             "Artificial Intelligence", "Dr. Shah");
    graduate.displayGraduateStudent();

    return 0;
}
