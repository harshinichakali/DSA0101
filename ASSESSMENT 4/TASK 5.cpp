#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Cart {
    string items[10];
    double prices[10];
    int n = 0;
    double discount = 0.0; // percent

public:

    // TODO 1: Add item and return *this
    Cart& add(string item, double price) {
        if (n < 10) {
            items[n] = item;
            prices[n] = price;
            n++;
        }
        return *this;
    }

    // TODO 2: Use this pointer
    Cart& setDiscount(double discount) {
        this->discount = discount;
        return *this;
    }

    // Calculate total
    double total() const {
        double t = 0;

        for (int i = 0; i < n; i++) {
            t += prices[i];
        }

        return t * (100 - discount) / 100;
    }
};

int main() {

    Cart c;

    // Method chaining
    c.add("Rice", 60)
     .add("Dal", 120)
     .setDiscount(10);

    // Pointer to an object
    Cart* p = &c;

    p->add("Oil", 180);

    // Four ways to access the object
    Cart& ref = c;
    Cart* p2 = &ref;

    cout << fixed << setprecision(2)
         << c.total() + p->total() << '\n';

    return 0;
}
