#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// Reads an integer safely. If the input is invalid, discard that line and retry.
int readInt(const string& prompt, int minimum, int maximum) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value) {
            if (value >= minimum && value <= maximum) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }

            cout << "Enter a value from " << minimum
                 << " to " << maximum << ".\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    constexpr long long MINIMUM_BALANCE_PAISE = 5'000;

    // Fares in paise: Rs 10, Rs 20 and Rs 30.
    const long long baseFares[] = {1'000, 2'000, 3'000};

    long long balancePaise = readInt("Enter card balance in rupees: ", 0, 1'000'000);
    balancePaise *= 100;

    const int zone = readInt("Enter farthest zone (1=Inner, 2=Middle, 3=Outer): ", 1, 3);
    const int hour = readInt("Enter journey hour (0-23): ", 0, 23);

    long long farePaise = baseFares[zone - 1];

    // Peak periods: 08:00–09:59 and 17:00–19:59.
    const bool isPeak = (hour >= 8 && hour < 10) ||
                        (hour >= 17 && hour < 20);

    if (isPeak) {
        farePaise = farePaise * 120 / 100;
    }

    cout << "\n--- Journey Report ---\n"
         << "Zone: " << (zone == 1 ? "Inner" : zone == 2 ? "Middle" : "Outer") << '\n'
         << "Time: " << setw(2) << setfill('0') << hour << ":00\n"
         << "Peak hour: " << boolalpha << isPeak << '\n'
         << fixed << setprecision(2)
         << "Fare: Rs " << static_cast<double>(farePaise) / 100.0 << '\n';

    if (balancePaise - farePaise >= MINIMUM_BALANCE_PAISE) {
        balancePaise -= farePaise;
        cout << "Journey approved.\n";
    } else {
        cout << "Journey denied: at least Rs 50.00 must remain on the card.\n";
    }

    cout << "Remaining balance: Rs "
         << static_cast<double>(balancePaise) / 100.0 << '\n';

    return 0;
}
