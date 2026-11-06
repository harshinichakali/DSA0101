
#include <iostream>
using namespace std;

class Money {
    long long rupees;
    int paise;

public:
    // Constructor
    Money(long long r = 0, int p = 0) {
        long long total = r * 100 + p;
        rupees = total / 100;
        paise = total % 100;

        if (paise < 0) {
            rupees--;
            paise += 100;
        }
    }

    // TODO 1: Overload + as a member function
    Money operator+(const Money& m) {
        long long total1 = rupees * 100 + paise;
        long long total2 = m.rupees * 100 + m.paise;

        long long total = total1 + total2;

        return Money(total / 100, total % 100);
    }

    // Overload +=
    Money& operator+=(const Money& m) {
        *this = *this + m;
        return *this;
    }

    // Overload -=
    Money& operator-=(const Money& m) {
        long long total1 = rupees * 100 + paise;
        long long total2 = m.rupees * 100 + m.paise;
        long long total = total1 - total2;

        rupees = total / 100;
        paise = total % 100;

        if (paise < 0) {
            rupees--;
            paise += 100;
        }

        return *this;
    }

    // TODO 2: Overload ==
    bool operator==(const Money& m) const {
        return rupees == m.rupees &&
               paise == m.paise;
    }

    // Friend function for <<
    friend ostream& operator<<(ostream& out, const Money& m) {
        out << "Rs " << m.rupees << ".";

        if (m.paise < 10)
            out << "0";

        out << m.paise;
        return out;
    }
};

int main() {
    Money a(120, 75), b(79, 25);

    Money c = a + b;

    cout << c << '\n';
    cout << boolalpha << (c == Money(200)) << '\n';

    // Test addition with paise carry
    Money d(10, 75), e(5, 50);
    Money f = d + e;

    cout << f << '\n';

    return 0;
}
