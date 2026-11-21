#include <iostream>
using namespace std;

struct Bill {
    virtual ~Bill() {
        cout << "~Bill ";
    }

    virtual double total() const = 0;

    virtual void show() const {
        cout << total() << " ";
    }
};

struct OPBill : Bill {
    ~OPBill() override {
        cout << "~OPBill ";
    }

    double total() const override {
        return 500;
    }
};

int main() {
    Bill* b = new OPBill;

    b->show();

    delete b;

    cout << '\n';
    return 0;
}
