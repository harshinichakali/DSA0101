#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// Abstract Base Class
class Vehicle {
protected:
    string regNo;
    double dailyRate;
    bool rented;

public:
    Vehicle(string r, double rate) {
        regNo = r;
        dailyRate = rate;
        rented = false;
    }

    virtual double rentalCharge(int days) = 0;

    virtual void display() {
        cout << "Registration Number: " << regNo << endl;
        cout << "Daily Rate: Rs." << dailyRate << endl;
        cout << "Status: " << (rented ? "Rented" : "Available") << endl;
    }

    void rentVehicle() {
        if (!rented) {
            rented = true;
            cout << regNo << " rented successfully." << endl;
        } else {
            cout << "Vehicle is already rented." << endl;
        }
    }

    void returnVehicle(int lateDays) {
        if (rented) {
            double lateCharge = lateDays * dailyRate * 0.5;
            cout << "Late Charge: Rs." << lateCharge << endl;
            rented = false;
            cout << regNo << " returned successfully." << endl;
        } else {
            cout << "Vehicle was not rented." << endl;
        }
    }

    virtual ~Vehicle() {}
};

// Bicycle Class
class Bicycle : public Vehicle {
public:
    Bicycle(string r, double rate) : Vehicle(r, rate) {}

    double rentalCharge(int days) override {
        return dailyRate * days;
    }

    void display() override {
        cout << "\nBICYCLE DETAILS" << endl;
        Vehicle::display();
    }
};

// Abstract Motor Vehicle Class
class MotorVehicle : public Vehicle {
protected:
    double fuelOrChargeLevel;
    string serviceDueDate;

public:
    MotorVehicle(string r, double rate, double level, string date)
        : Vehicle(r, rate) {
        fuelOrChargeLevel = level;
        serviceDueDate = date;
    }

    void display() override {
        Vehicle::display();
        cout << "Fuel/Charge Level: " << fuelOrChargeLevel << endl;
        cout << "Service Due Date: " << serviceDueDate << endl;
    }
};

// Two Wheeler Class
class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(string r, double rate, double fuel, string date)
        : MotorVehicle(r, rate, fuel, date) {}

    double rentalCharge(int days) override {
        return dailyRate * days + 100;
    }

    void display() override {
        cout << "\nTWO WHEELER DETAILS" << endl;
        MotorVehicle::display();
    }
};

// Car Class
class Car : public MotorVehicle {
protected:
    int seatingCapacity;

public:
    Car(string r, double rate, double fuel, string date, int seats)
        : MotorVehicle(r, rate, fuel, date) {
        seatingCapacity = seats;
    }

    double rentalCharge(int days) override {
        return dailyRate * days + 200;
    }

    void display() override {
        cout << "\nCAR DETAILS" << endl;
        MotorVehicle::display();
        cout << "Seating Capacity: " << seatingCapacity << endl;
    }
};

// Electric Car Class
class ElectricCar : public Car {
private:
    double batteryCapacity;
    double kWhUsed;
    double pricePerKWh;

public:
    ElectricCar(string r, double rate, double level,
                string date, int seats, double battery,
                double used, double price)
        : Car(r, rate, level, date, seats) {
        batteryCapacity = battery;
        kWhUsed = used;
        pricePerKWh = price;
    }

    double rentalCharge(int days) override {
        return dailyRate * days + kWhUsed * pricePerKWh;
    }

    void display() override {
        cout << "\nELECTRIC CAR DETAILS" << endl;
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

// New Vehicle Type - Electric Bus
class ElectricBus : public MotorVehicle {
private:
    int seatingCapacity;
    double batteryCapacity;
    double kWhUsed;

public:
    ElectricBus(string r, double rate, double level,
                string date, int seats, double battery,
                double used)
        : MotorVehicle(r, rate, level, date) {
        seatingCapacity = seats;
        batteryCapacity = battery;
        kWhUsed = used;
    }

    double rentalCharge(int days) override {
        return dailyRate * days + kWhUsed * 10;
    }

    void display() override {
        cout << "\nELECTRIC BUS DETAILS" << endl;
        MotorVehicle::display();
        cout << "Seating Capacity: " << seatingCapacity << endl;
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

// Main Function
int main() {

    vector<unique_ptr<Vehicle>> fleet;

    fleet.push_back(make_unique<Bicycle>("BIKE101", 100));
    fleet.push_back(make_unique<TwoWheeler>("TW102", 300, 80, "20-12-2026"));
    fleet.push_back(make_unique<Car>("CAR103", 1000, 60, "25-12-2026", 5));
    fleet.push_back(make_unique<ElectricCar>("EC104", 1500, 90,
                     "30-12-2026", 5, 60, 20, 10));

    // Adding a new vehicle type without changing existing classes
    fleet.push_back(make_unique<ElectricBus>("BUS105", 3000, 85,
                     "31-12-2026", 40, 150, 50));

    cout << "===== VEHICLE RENTAL FLEET =====" << endl;

    // Display all vehicles
    for (auto &v : fleet) {
        v->display();
        cout << "Rental Charge for 2 Days: Rs."
             << v->rentalCharge(2) << endl;
        cout << "-----------------------------" << endl;
    }

    // Demonstrate renting a vehicle
    cout << "\n===== RENTING VEHICLE =====" << endl;
    fleet[0]->rentVehicle();

    // Demonstrate returning with late charge
    cout << "\n===== RETURNING VEHICLE =====" << endl;
    fleet[0]->returnVehicle(2);

    // Demonstrate adding a new vehicle
    cout << "\n===== NEW VEHICLE ADDED =====" << endl;
    cout << "Electric Bus added successfully!" << endl;

    cout << "\n===== UPDATED FLEET =====" << endl;

    for (auto &v : fleet) {
        v->display();
        cout << "Rental Charge: Rs."
             << v->rentalCharge(2) << endl;
    }

    return 0;
}
