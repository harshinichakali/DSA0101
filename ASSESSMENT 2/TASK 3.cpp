
#include <iostream>
using namespace std;

struct Parcel
{
    double weightKg;
    bool express;
    bool insured;
};

// Calculate courier charge
double calculateCharge(double weight, bool express, bool insured)
{
    double charge = weight * 40;

    if (express)
        charge += 30;

    if (insured)
        charge += 20;

    return charge;
}

// Overloading for weight in kilograms
double charge(double weight, bool express = false,
              bool insured = false)
{
    return calculateCharge(weight, express, insured);
}

// Overloading for weight in grams
double charge(int weight, bool express = false,
              bool insured = false)
{
    double kg = weight / 1000.0;
    return calculateCharge(kg, express, insured);
}

// Overloading for Parcel object
double charge(const Parcel& p)
{
    return calculateCharge(p.weightKg, p.express, p.insured);
}

int main()
{
    Parcel p = {5.0, true, true};

    cout << "Courier Charge Calculator" << endl;

    // Six function calls
    cout << "1. charge(2): "
         << charge(2) << endl;

    cout << "2. charge(2.0): "
         << charge(2.0) << endl;

    cout << "3. charge(2000): "
         << charge(2000) << endl;

    cout << "4. charge(2.5, true): "
         << charge(2.5, true) << endl;

    cout << "5. charge(Parcel): "
         << charge(p) << endl;

    cout << "6. charge(3000, false, true): "
         << charge(3000, false, true) << endl;

    return 0;
}
