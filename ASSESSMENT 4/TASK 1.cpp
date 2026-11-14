#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Common Base Class
class Staff {
protected:
    string name;
    int id;

public:
    Staff(string n, int i) {
        name = n;
        id = i;
    }

    virtual double pay() const = 0;

    virtual void display() const {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Pay: Rs. " << pay() << endl;
    }

    virtual ~Staff() {}
};

// Derived Class 1
class Professor : public Staff {
private:
    double basic, research;

public:
    Professor(string n, int i, double b, double r)
        : Staff(n, i) {
        basic = b;
        research = r;
    }

    double pay() const override {
        return basic + basic * 0.42 + research;
    }
};

// Derived Class 2
class LabAssistant : public Staff {
private:
    double basic;

public:
    LabAssistant(string n, int i, double b)
        : Staff(n, i) {
        basic = b;
    }

    double pay() const override {
        return basic + basic * 0.42;
    }
};

// Derived Class 3
class GuestFaculty : public Staff {
private:
    double hours, rate;

public:
    GuestFaculty(string n, int i, double h, double r)
        : Staff(n, i) {
        hours = h;
        rate = r;
    }

    double pay() const override {
        return hours * rate;
    }
};

// Main Function
int main() {
    vector<unique_ptr<Staff>> staff;

    staff.push_back(
        make_unique<Professor>("Arun", 101, 50000, 10000)
    );

    staff.push_back(
        make_unique<LabAssistant>("Priya", 102, 30000)
    );

    staff.push_back(
        make_unique<GuestFaculty>("Kumar", 103, 40, 500)
    );

    cout << "COLLEGE PAYROLL SYSTEM" << endl;
    cout << "----------------------" << endl;

    for (const auto& s : staff) {
        s->display();
        cout << "----------------------" << endl;
    }

    return 0;
}
