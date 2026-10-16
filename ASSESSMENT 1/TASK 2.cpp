#include <iostream>
using namespace std;

// enum class gives zones a distinct type and prevents accidental mixing
// with unrelated integers or enums.
enum class Zone {
    Inner = 1,
    Middle,
    Outer
};

// Fare rules are kept in one place. constexpr values can be used at compile time.
namespace FareRules {
    constexpr int INNER_FARE_RUPEES = 10;
    constexpr int MIDDLE_FARE_RUPEES = 20;
    constexpr int OUTER_FARE_RUPEES = 30;

    constexpr int SURCHARGE_PERCENT = 20;
    constexpr int MIN_BALANCE_AFTER_JOURNEY_RUPEES = 50;
}

constexpr int baseFare(Zone zone) {
    switch (zone) {
        case Zone::Inner:  return FareRules::INNER_FARE_RUPEES;
        case Zone::Middle: return FareRules::MIDDLE_FARE_RUPEES;
        case Zone::Outer:  return FareRules::OUTER_FARE_RUPEES;
    }
    return 0; // Fallback for invalid input.
}

constexpr int calculateFare(Zone zone, bool isPeakTime) {
    const int fare = baseFare(zone);

    // All current fares are divisible by 5, so this integer calculation
    // gives the exact 20% surcharge in whole rupees.
    return isPeakTime
        ? fare * (100 + FareRules::SURCHARGE_PERCENT) / 100
        : fare;
}

int main() {
    const Zone journeyZone = Zone::Outer;
    const bool isPeakTime = true;

    const int fare = calculateFare(journeyZone, isPeakTime);

    cout << "Fare: Rs " << fare << '\n';
    cout << "Minimum balance after journey: Rs "
         << FareRules::MIN_BALANCE_AFTER_JOURNEY_RUPEES << '\n';

    return 0;
}
