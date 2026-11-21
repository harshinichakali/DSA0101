#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <iomanip>
using namespace std;
using namespace chrono;

class Bill {
public:
    double amount;

    Bill(double a) {
        amount = a;
    }

    virtual double calculate() const {
        return amount;
    }

    virtual ~Bill() {}
};

class OutPatientBill : public Bill {
public:
    OutPatientBill(double a) : Bill(a) {}

    double calculate() const override {
        return amount;
    }
};

class InPatientBill : public Bill {
public:
    InPatientBill(double a) : Bill(a) {}

    double calculate() const override {
        return amount;
    }
};

// Switch-based approach
struct SwitchBill {
    double amount;
    int type;
};

double switchCalculate(const SwitchBill& b) {
    switch (b.type) {
        case 1: return b.amount;
        case 2: return b.amount;
        default: return 0;
    }
}

// Return-code validation
bool validateReturn(double amount, double& result) {
    if (amount < 0)
        return false;

    result = amount;
    return true;
}

// Exception-based validation
double validateException(double amount) {
    if (amount < 0)
        throw invalid_argument("Invalid bill amount");

    return amount;
}

int main() {
    double values[] = {
        1000, 1500, 2000, 2500, 3000,
        3500, 4000, 4500, 5000, 5500
    };

    cout << "B3.1 - CORRECTNESS ON SMALL DATA" << endl;

    double totalVirtual = 0;
    double totalSwitch = 0;

    for (int i = 0; i < 10; i++) {
        OutPatientBill b(values[i]);
        totalVirtual += b.calculate();

        SwitchBill s = {values[i], 1};
        totalSwitch += switchCalculate(s);
    }

    cout << "Virtual Function Total: "
         << totalVirtual << endl;

    cout << "Switch Total: "
         << totalSwitch << endl;

    cout << "\nB3.2 - INCREASE DATA SIZE" << endl;

    for (int n : {1000000, 10000000}) {
        vector<double> bills(n, 100.0);

        auto start = high_resolution_clock::now();

        double total = 0;

        for (double amount : bills)
            total += amount;

        auto stop = high_resolution_clock::now();

        cout << "Bills: " << n
             << " Total: " << total
             << " Time: "
             << duration<double, milli>(
                    stop - start).count()
             << " ms" << endl;
    }

    cout << "\nB3.3 - COST OF EXCEPTIONS" << endl;

    const int N = 1000000;

    for (int rate : {0, 1, 50}) {
        double total = 0;
        int errors = 0;

        auto start = high_resolution_clock::now();

        for (int i = 0; i < N; i++) {
            double amount =
                (i % 100 < rate) ? -100 : 100;

            double result;

            if (validateReturn(amount, result))
                total += result;
            else
                errors++;
        }

        auto stop = high_resolution_clock::now();

        cout << "Return Code - Invalid "
             << rate << "%, Errors: " << errors
             << ", Time: "
             << duration<double, milli>(
                    stop - start).count()
             << " ms" << endl;

        total = 0;
        errors = 0;

        start = high_resolution_clock::now();

        for (int i = 0; i < N; i++) {
            double amount =
                (i % 100 < rate) ? -100 : 100;

            try {
                total += validateException(amount);
            }
            catch (const invalid_argument&) {
                errors++;
            }
        }

        stop = high_resolution_clock::now();

        cout << "Exception - Invalid "
             << rate << "%, Errors: " << errors
             << ", Time: "
             << duration<double, milli>(
                    stop - start).count()
             << " ms" << endl;
    }

    cout << "\nB3.4 - ENGINEERING TRADE-OFF" << endl;

    cout << "Virtual Functions: Flexible and extensible."
         << endl;

    cout << "Switch: Simple and efficient for fixed types."
         << endl;

    cout << "Return Codes: Efficient for frequent errors."
         << endl;

    cout << "Exceptions: Suitable for rare exceptional errors."
         << endl;

    return 0;
}
