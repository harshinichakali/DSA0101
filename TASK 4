#include <iostream>

int main() {
    int a = 7;
    int b = 2;

    // Integer division happens first: 7 / 2 is 3.
    double c = a / b;

    // Casting before division gives floating-point division: 3.5.
    double d = static_cast<double>(a) / b;

    std::cout << c << ' ' << d << '\n';

    // 'A' is promoted to int; 65 + 2 is converted back to char ('C').
    char ch = 'A' + 2;
    std::cout << ch << ' ' << ch + 1 << '\n';

    // The non-zero integer 5 converts to true.
    bool flag = 5;
    std::cout << flag << ' ' << std::boolalpha << flag << '\n';

    unsigned int u = 1;
    int s = -1;

    // s is converted to unsigned int for this comparison.
    std::cout << (s < u ? "s < u" : "s >= u") << '\n';

    return 0;
}
