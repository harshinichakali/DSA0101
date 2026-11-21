#include <iostream>
#include <exception>
#include <string>
#include <vector>
using namespace std;

// Base Exception Class
class BillingError : public exception {
protected:
    string message;

public:
    BillingError(string msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    virtual ~BillingError() noexcept = default;
};

// Negative Charge Exception
class NegativeChargeError : public BillingError {
public:
    NegativeChargeError() : BillingError("Error: Negative charge is not allowed!") {}
};

// Claim Error
class ClaimError : public BillingError {
public:
    ClaimError() : BillingError("Error: Claim amount exceeds insurance cover!") {}
};

// Unknown Package Exception
class UnknownPackageError : public BillingError {
public:
    UnknownPackageError() : BillingError("Error: Unknown treatment package!") {}
};

// Missing Patient Exception
class MissingPatientRecordError : public BillingError {
public:
    MissingPatientRecordError() : BillingError("Error: Patient record not found!") {}
};

// Patient Structure
struct Patient {
    int id;
    string name;
};

// Billing Function
double calculateBill(double charge, double cover,
                     string packageName, bool patientExists) {

    if (!patientExists)
        throw MissingPatientRecordError();

    if (charge < 0)
        throw NegativeChargeError();

    if (packageName != "Surgery" &&
        packageName != "Consultation" &&
        packageName != "Scan")
        throw UnknownPackageError();

    if (charge > cover)
        throw ClaimError();

    return charge;
}

// Main Function
int main() {
    try {
        vector<Patient> patients;

        patients.push_back({101, "Arun"});

        double charge = 5000;
        double cover = 6000;
        string packageName = "Surgery";

        bool patientExists = true;

        double amount = calculateBill(
            charge, cover, packageName, patientExists
        );

        cout << "Billing Successful!" << endl;
        cout << "Patient: " << patients[0].name << endl;
        cout << "Package: " << packageName << endl;
        cout << "Bill Amount: Rs. " << amount << endl;
    }
    catch (const BillingError& e) {
        cout << e.what() << endl;
    }
    catch (const bad_alloc& e) {
        cout << "Memory allocation failure!" << endl;
    }
    catch (const exception& e) {
        cout << "General Error: " << e.what() << endl;
    }

    return 0;
}
