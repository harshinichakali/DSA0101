#include <iostream>
#include <vector>
#include <memory>
#include <array>
using namespace std;

// Base Class
class Account {
public:
    virtual double rate() const {
        return 3.5;
    }

    virtual ~Account() {
        cout << "Account Destructor" << endl;
    }
};

// Derived Class
class SeniorAccount : public Account {
private:
    array<double, 100> history{};

public:
    double rate() const override {
        return 4.0;
    }

    ~SeniorAccount() override {
        cout << "SeniorAccount Destructor" << endl;
    }
};

int main() {

    // Using smart pointers
    vector<unique_ptr<Account>> accounts;

    accounts.push_back(make_unique<Account>());
    accounts.push_back(make_unique<SeniorAccount>());

    // Display interest rates
    for (const auto& a : accounts) {
        cout << "Interest Rate: " << a->rate() << "%" << endl;
    }

    // Using reference to prevent object slicing
    Account& copy = *accounts[1];

    cout << "Reference Rate: " << copy.rate() << "%" << endl;

    return 0;
}
