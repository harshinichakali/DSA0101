#include <iostream>
#include <climits>
#include <cstdint>
#include <limits>

using namespace std;

enum class Zone : int {
    Inner = 1,
    Middle = 2,
    Outer = 3
};

namespace FareRules {
    // All monetary values are stored in paise: Rs 1 = 100 paise.
    constexpr long long INNER_FARE_PAISE = 1'000;
    constexpr long long MIDDLE_FARE_PAISE = 2'000;
    constexpr long long OUTER_FARE_PAISE = 3'000;

    constexpr int PEAK_SURCHARGE_PERCENT = 20;
    constexpr long long MINIMUM_BALANCE_PAISE = 5'000; // Rs 50
}

struct JourneyRequest {
    Zone farthestZone;
    bool isPeakTime;
    bool getsConcession;
};

long long baseFare(Zone zone) {
    switch (zone) {
        case Zone::Inner:  return FareRules::INNER_FARE_PAISE;
        case Zone::Middle: return FareRules::MIDDLE_FARE_PAISE;
        case Zone::Outer:  return FareRules::OUTER_FARE_PAISE;
    }

    return 0; // Invalid zone fallback.
}

long long calculateFare(const JourneyRequest& journey) {
    long long fare = baseFare(journey.farthestZone);

    if (journey.isPeakTime) {
        fare = fare * (100 + FareRules::PEAK_SURCHARGE_PERCENT) / 100;
    }

    // Assumption: the student/senior concession is 50%,
    // applied after the peak surcharge.
    if (journey.getsConcession) {
        fare /= 2;
    }

    return fare;
}

bool payFare(long long& cardBalancePaise, long long farePaise) {
    if (farePaise < 0 ||
        cardBalancePaise - farePaise < FareRules::MINIMUM_BALANCE_PAISE) {
        return false;
    }

    cardBalancePaise -= farePaise;
    return true;
}

int main() {
    // long long is used for balances and accumulated collections.
    long long cardBalancePaise = 10'000; // Rs 100

    const JourneyRequest journey{
        Zone::Outer,
        true,  // peak time
        true   // concession eligible
    };

    const long long farePaise = calculateFare(journey);

    cout << "Fare: Rs " << farePaise / 100 << "."
         << (farePaise % 100 < 10 ? "0" : "")
         << farePaise % 100 << '\n';

    if (payFare(cardBalancePaise, farePaise)) {
        cout << "Journey approved.\n";
    } else {
        cout << "Journey denied: at least Rs 50 must remain.\n";
    }

    cout << "Remaining balance: Rs " << cardBalancePaise / 100 << "."
         << (cardBalancePaise % 100 < 10 ? "0" : "")
         << cardBalancePaise % 100 << '\n';

    // Type and range information for this system.
    cout << "\nType sizes on this system:\n"
         << "bool: " << sizeof(bool) << " byte(s)\n"
         << "char: " << sizeof(char) << " byte(s)\n"
         << "int: " << sizeof(int) << " byte(s)\n"
         << "long long: " << sizeof(long long) << " byte(s)\n"
         << "double: " << sizeof(double) << " byte(s)\n";

    cout << "\nint range: " << INT_MIN << " to " << INT_MAX << '\n';
    cout << "long long range: " << LLONG_MIN << " to " << LLONG_MAX << '\n';

    // The maximum possible one-day collection if every journey paid Rs 36:
    constexpr long long JOURNEYS_PER_DAY = 3'000'000;
    constexpr long long MAX_FARE_PAISE = 3'600; // Rs 36
    constexpr long long MAX_DAILY_COLLECTION_PAISE =
        JOURNEYS_PER_DAY * MAX_FARE_PAISE;

    cout << "Maximum example daily collection: Rs "
         << MAX_DAILY_COLLECTION_PAISE / 100 << '\n';

    return 0;
}
