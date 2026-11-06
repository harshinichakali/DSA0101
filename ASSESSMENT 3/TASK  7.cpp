
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    // Default constructor
    Complex() {
        real = 0;
        imag = 0;
    }

    // Parameterized constructor
    Complex(double r, double i = 0) {
        real = r;
        imag = i;
    }

    // Overload + operator
    Complex operator+(const Complex& c) const {
        return Complex(real + c.real, imag + c.imag);
    }

    // Overload - operator
    Complex operator-(const Complex& c) const {
        return Complex(real - c.real, imag - c.imag);
    }

    // Overload * operator
    Complex operator*(const Complex& c) const {
        return Complex(
            real * c.real - imag * c.imag,
            real * c.imag + imag * c.real
        );
    }

    // Overload / operator
    Complex operator/(const Complex& c) const {
        double denominator =
            c.real * c.real + c.imag * c.imag;

        if (denominator == 0) {
            throw runtime_error("Division by zero impedance!");
        }

        return Complex(
            (real * c.real + imag * c.imag) / denominator,
            (imag * c.real - real * c.imag) / denominator
        );
    }

    // Overload == operator
    bool operator==(const Complex& c) const {
        return real == c.real && imag == c.imag;
    }

    // Calculate magnitude
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }

    // Friend function for output
    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << c.real;

        if (c.imag >= 0)
            out << " + " << c.imag << "j";
        else
            out << " - " << -c.imag << "j";

        return out;
    }
};

int main() {
    cout << fixed << setprecision(2);

    // Create complex impedance objects
    Complex R(10, 0);
    Complex L(0, 6);
    Complex C(0, -2);

    // Series RLC circuit
    Complex series = R + L + C;

    cout << "Series Impedance: " << series << endl;
    cout << "Series Magnitude: " << series.magnitude() << endl;

    // Parallel impedance calculation
    Complex Z1(10, 6);
    Complex Z2(0, -2);

    Complex parallel = (Z1 * Z2) / (Z1 + Z2);

    cout << "\nParallel Impedance: " << parallel << endl;
    cout << "Parallel Magnitude: "
         << parallel.magnitude() << endl;

    // Operator testing
    Complex a(5, 3);
    Complex b(2, 1);

    cout << "\nAddition: " << a + b << endl;
    cout << "Subtraction: " << a - b << endl;
    cout << "Multiplication: " << a * b << endl;
    cout << "Division: " << a / b << endl;

    cout << boolalpha;
    cout << "Equality: " << (a == b) << endl;

    // Division by zero testing
    try {
        Complex zero(0, 0);
        Complex result = a / zero;
        cout << result << endl;
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
