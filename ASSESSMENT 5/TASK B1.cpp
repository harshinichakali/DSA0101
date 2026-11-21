#include <iostream>
#include <string>
using namespace std;

// Base Class
class Bill {
protected:
    string patient;

public:
    explicit Bill(const string& p) : patient(p) {}

    virtual ~Bill() = default;

    // TODO 1: Pure virtual functions
    virtual double total() const = 0;
    virtual string type() const = 0;

    void print() const {
        cout << type() << " " << patient << " "
             << total() << "\n";
    }
};

// OutPatient Bill
class OutPatient : public Bill {
    double consultation, tests;

public:
    OutPatient(const string& p, double c, double t)
        : Bill(p), consultation(c), tests(t) {}

    // TODO 2: Override total() and type()
    double total() const override {
        return consultation + tests;
    }

    string type() const override {
        return "OP";
    }
};

// InPatient Bill
class InPatient : public Bill {
    int days;
    double perDay, surgery;

public:
    InPatient(const string& p, int d, double rate, double s)
        : Bill(p), days(d), perDay(rate), surgery(s) {}

    // TODO 3: Override total() and type()
    double total() const override {
        return days * perDay + surgery;
    }

    string type() const override {
        return "IP";
    }
};

int main() {
    Bill* bills[] = {
        new OutPatient("Ravi", 500, 1200),
        new InPatient("Meena", 3, 2500, 40000)
    };

    double sum = 0;

    for (Bill* b : bills) {
        b->print();             // Runtime polymorphism
        sum += b->total();
    }

    cout << "Total " << sum << "\n";

    // Virtual destructor runs the correct destructor
    for (Bill* b : bills) {
        delete b;
    }

    return 0;
}
