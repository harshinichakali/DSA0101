#include <iostream>
#include <string>
using namespace std;

// RAII Guard Class
struct Guard {
    string n;

    explicit Guard(const string& s) : n(s) {}

    ~Guard() {
        cout << "~" << n << '\n';
    }
};

// Function that throws an exception
void f() {
    Guard g("f");
    throw 42;
}

// Main Function
int main() {
    try {
        Guard g("main");
        f();
        cout << "not printed";
    }
    catch (int x) {
        cout << "caught " << x;
    }
    catch (...) {
        cout << "other";
    }

    cout << '\n';
    return 0;
}
