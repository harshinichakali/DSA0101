#include <iostream>
using namespace std;

// Base Class
struct Person {
    Person() {
        cout << "Person ";
    }
};

// Derived Class 1
struct Student : virtual Person {
    Student() {
        cout << "Student ";
    }
};

// Derived Class 2
struct Staff : virtual Person {
    Staff() {
        cout << "Staff ";
    }
};

// Multiple Inheritance
struct TeachingAssistant : Student, Staff {
    TeachingAssistant() {
        cout << "TA ";
    }
};

// Main Function
int main() {
    TeachingAssistant ta;

    cout << endl;

    return 0;
}
