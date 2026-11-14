#include <iostream>
using namespace std;

struct Engine {
    Engine() {
        cout << "Engine ";
    }

    ~Engine() {
        cout << "~Engine ";
    }
};

struct Vehicle {
    Vehicle() {
        cout << "Vehicle ";
    }

    ~Vehicle() {
        cout << "~Vehicle ";
    }
};

struct Car : Vehicle {
    Engine e;

    Car() {
        cout << "Car ";
    }

    ~Car() {
        cout << "~Car ";
    }
};

int main() {
    Car c;

    cout << "1";
    cout << "\n";

    return 0;
}
