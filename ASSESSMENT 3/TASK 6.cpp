#include <iostream>
#include <cstring>
using namespace std;

class Text {
private:
    char* data;

public:
    // Constructor
    Text(const char* str = "") {
        if (str == nullptr)
            str = "";

        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    // Copy constructor
    Text(const Text& other) {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    // Copy assignment operator
    Text& operator=(const Text& other) {
        if (this != &other) {
            char* temp = new char[strlen(other.data) + 1];
            strcpy(temp, other.data);

            delete[] data;
            data = temp;
        }
        return *this;
    }

    // Overload + for concatenation
    Text operator+(const Text& other) const {
        int len = strlen(data) + strlen(other.data);

        char* temp = new char[len + 1];

        strcpy(temp, data);
        strcat(temp, other.data);

        Text result(temp);

        delete[] temp;

        return result;
    }

    // Overload == for comparison
    bool operator==(const Text& other) const {
        return strcmp(data, other.data) == 0;
    }

    // Overload != for comparison
    bool operator!=(const Text& other) const {
        return !(*this == other);
    }

    // Friend function for printing
    friend ostream& operator<<(ostream& out, const Text& t) {
        out << t.data;
        return out;
    }

    // Destructor
    ~Text() {
        delete[] data;
    }
};

int main() {

    // Create Text objects
    Text a("Hello ");
    Text b("World");
    Text c("!");

    // Concatenation
    Text result = a + b + c;

    cout << "Concatenated Text: " << result << endl;

    // Comparison
    Text x("Hello");
    Text y("Hello");

    cout << boolalpha;
    cout << "Equal: " << (x == y) << endl;
    cout << "Not Equal: " << (x != y) << endl;

    // Copy constructor
    Text copy = a;
    cout << "Copied Text: " << copy << endl;

    // Self assignment
    a = a;
    cout << "Self Assignment: " << a << endl;

    // Empty message
    Text empty("");
    cout << "Empty Text: [" << empty << "]" << endl;

    // Long message
    Text longMsg("This is a long message for testing dynamic memory allocation.");
    cout << "Long Message: " << longMsg << endl;

    return 0;
}
