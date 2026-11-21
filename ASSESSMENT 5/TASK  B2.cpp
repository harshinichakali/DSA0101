#include <iostream>
#include <stdexcept>
#include <memory>
#include <limits>
using namespace std;

// Custom exception
class ClaimError : public runtime_error {
public:
    using runtime_error::runtime_error;
};

// RAII class to demonstrate object destruction
class Resource {
public:
    Resource() {
        cout << "Resource created" << endl;
    }

    ~Resource() {
        cout << "Resource destroyed" << endl;
    }
};

// Validate claim amount
double approve(double billed, double cover) {
    if (billed < 0 || cover < 0) {
        throw invalid_argument("negative amount");
    }

    if (billed > cover) {
        throw ClaimError("exceeds cover");
    }

    return billed;
}

// Handle and rethrow custom exception
double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    }
    catch (const ClaimError& e) {
        cout << "audit: " << e.what() << endl;
        throw;
    }
}

// Validate package code
void validatePackage(int code) {
    if (code < 1 || code > 3) {
        throw invalid_argument("unknown package code");
    }
}

// Demonstrate memory allocation exception
void testMemoryAllocation() {
    try {
        size_t size = numeric_limits<size_t>::max();
        unique_ptr<int[]> data(new int[size]);
    }
    catch (const bad_alloc& e) {
        cout << "Memory allocation failed" << endl;
    }
}

int main() {
    double claims[] = {400000, 600000, -1};
    double cover = 500000;

    for (double claim : claims) {
        try {
            Resource resource;

            double paid = settle(claim, cover);

            cout << "approved: " << paid << endl;
        }
        catch (const ClaimError& e) {
            cout << "claim rejected: " << e.what() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "error: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "error: " << e.what() << endl;
        }
    }

    // Test unknown package code
    try {
        validatePackage(5);
    }
    catch (const invalid_argument& e) {
        cout << "Package error: " << e.what() << endl;
    }

    // Test memory allocation failure
    testMemoryAllocation();

    cout << "Program continues running" << endl;

    return 0;
}
