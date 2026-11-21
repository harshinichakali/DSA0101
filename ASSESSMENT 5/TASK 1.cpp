#include <iostream>
#include <vector>
using namespace std;

// Abstract Base Class
class Bill {
public:
    virtual double total() = 0;       // Pure virtual function
    virtual string type() = 0;        // Pure virtual function
    virtual void print() = 0;         // Pure virtual function

    virtual ~Bill() {}
};

// Derived Class: Electricity Bill
class ElectricityBill : public Bill {
private:
    double units;
    double rate;

public:
    ElectricityBill(double u, double r) {
        units = u;
        rate = r;
    }

    double total() override {
        return units * rate;
    }

    string type() override {
        return "Electricity Bill";
    }

    void print() override {
        cout << type() << " : Rs. " << total() << endl;
    }
};

// Derived Class: Water Bill
class WaterBill : public Bill {
private:
    double liters;
    double rate;

public:
    WaterBill(double l, double r) {
        liters = l;
        rate = r;
    }

    double total() override {
        return liters * rate;
    }

    string type() override {
        return "Water Bill";
    }

    void print() override {
        cout << type() << " : Rs. " << total() << endl;
    }
};

// Derived Class: Gas Bill
class GasBill : public Bill {
private:
    double quantity;
    double rate;

public:
    GasBill(double q, double r) {
        quantity = q;
        rate = r;
    }

    double total() override {
        return quantity * rate;
    }

    string type() override {
        return "Gas Bill";
    }

    void print() override {
        cout << type() << " : Rs. " << total() << endl;
    }
};

// Main Function
int main() {
    vector<Bill*> bills;

    bills.push_back(new ElectricityBill(100, 5));
    bills.push_back(new WaterBill(200, 2));
    bills.push_back(new GasBill(50, 10));

    double grandTotal = 0;

    cout << "----- Bill Details -----" << endl;

    for (Bill* b : bills) {
        b->print();
        grandTotal += b->total();
    }

    cout << "\nDay's Total = Rs. " << grandTotal << endl;

    // Free memory
    for (Bill* b : bills) {
        delete b;
    }

    return 0;
}
