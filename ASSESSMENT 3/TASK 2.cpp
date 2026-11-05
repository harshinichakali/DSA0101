#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class Prescription {
private:
    int count;
    std::string* medicines; // Dynamically allocated array

public:
    explicit Prescription(int medicineCount)
        : count(medicineCount),
          medicines(medicineCount > 0 ? new std::string[medicineCount] : nullptr) {
        if (medicineCount < 0) {
            throw std::invalid_argument("Medicine count cannot be negative.");
        }
    }

    // Deep-copy constructor: allocates a separate array and copies each medicine.
    Prescription(const Prescription& other)
        : count(other.count),
          medicines(other.count > 0 ? new std::string[other.count] : nullptr) {
        for (int i = 0; i < count; ++i) {
            medicines[i] = other.medicines[i];
        }
    }

    // Copy assignment: handles self-assignment and replaces the old array safely.
    Prescription& operator=(const Prescription& other) {
        if (this == &other) {
            return *this;
        }

        std::string* newMedicines =
            other.count > 0 ? new std::string[other.count] : nullptr;

        for (int i = 0; i < other.count; ++i) {
            newMedicines[i] = other.medicines[i];
        }

        delete[] medicines;
        medicines = newMedicines;
        count = other.count;

        return *this;
    }

    // Destructor: releases the dynamically allocated array.
    ~Prescription() {
        delete[] medicines;
    }

    void set(int index, const std::string& medicine) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Medicine index is out of range.");
        }
        medicines[index] = medicine;
    }

    const std::string& get(int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Medicine index is out of range.");
        }
        return medicines[index];
    }
};

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p; // Calls copy constructor.
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p; // Calls copy assignment operator.
    r.set(0, "Ibuprofen");

    std::cout << q.get(0) << " | " << q.get(1) << " | "
              << p.get(0) << " " << p.get(1) << " | "
              << r.get(0) << " " << r.get(1) << '\n';
}
