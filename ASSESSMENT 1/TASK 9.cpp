#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum class Zone {
    Inner,
    Middle,
    Outer
};

constexpr long long INNER_FARE_PAISE = 1'000; // Rs 10
constexpr long long MIDDLE_FARE_PAISE = 2'000; // Rs 20
constexpr long long OUTER_FARE_PAISE = 3'000; // Rs 30
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MINIMUM_REMAINING_PAISE = 5'000; // Rs 50

bool isPeakTime(int hour) {
    if (hour < 0 || hour > 23) {
        return false;
    }

    // Peak periods are [08:00, 10:00) and [17:00, 20:00).
    return (hour >= 8 && hour < 10) ||
           (hour >= 17 && hour < 20);
}

long long baseFare(Zone zone) {
    switch (zone) {
        case Zone::Inner:  return INNER_FARE_PAISE;
        case Zone::Middle: return MIDDLE_FARE_PAISE;
        case Zone::Outer:  return OUTER_FARE_PAISE;
    }

    return 0; // Invalid zone fallback.
}

long long calculateFare(Zone zone, int hour) {
    long long fare = baseFare(zone);

    if (isPeakTime(hour)) {
        fare = fare * (100 + PEAK_SURCHARGE_PERCENT) / 100;
    }

    return fare;
}

bool canTravel(long long balancePaise, long long farePaise) {
    return farePaise >= 0 &&
           balancePaise >= farePaise + MINIMUM_REMAINING_PAISE;
}

bool parseZone(const std::string& input, Zone& zone) {
    std::istringstream stream(input);
    int value;
    char extra;

    if (!(stream >> value) || (stream >> extra)) {
        return false;
    }

    switch (value) {
        case 1: zone = Zone::Inner;  return true;
        case 2: zone = Zone::Middle; return true;
        case 3: zone = Zone::Outer;  return true;
        default: return false;
    }
}

bool parseHour(const std::string& input, int& hour) {
    std::istringstream stream(input);
    char extra;

    if (!(stream >> hour) || (stream >> extra)) {
        return false;
    }

    return hour >= 0 && hour <= 23;
}

bool parseRecharge(const std::string& input, long long& rechargePaise) {
    std::istringstream stream(input);
    long long rupees;
    char extra;

    if (!(stream >> rupees) || (stream >> extra) || rupees < 0) {
        return false;
    }

    rechargePaise = rupees * 100;
    return true;
}

std::string zoneName(Zone zone) {
    switch (zone) {
        case Zone::Inner:  return "Inner";
        case Zone::Middle: return "Middle";
        case Zone::Outer:  return "Outer";
    }
    return "Unknown";
}

void printMoney(long long paise) {
    std::cout << "Rs " << paise / 100 << '.';
    if (paise % 100 < 10) {
        std::cout << '0';
    }
    std::cout << paise % 100;
}

int main() {
    struct TestCase {
        Zone zone;
        int hour;
        long long expectedFarePaise;
    };

    // Five journeys, including peak/off-peak and boundary-hour cases.
    const std::vector<TestCase> tests = {
        {Zone::Inner,  7,  1'000}, // Rs 10, off-peak
        {Zone::Middle, 8,  2'400}, // Rs 24, peak at 08:00
        {Zone::Outer, 10, 3'000},  // Rs 30, off-peak at 10:00
        {Zone::Inner, 17, 1'200},  // Rs 12, peak at 17:00
        {Zone::Outer, 20, 3'000}   // Rs 30, off-peak at 20:00
    };

    std::cout << "Fare test results\n";
    std::cout << "Zone     Hour   Expected   Actual     Result\n";

    long long totalFarePaise = 0;
    bool allPassed = true;

    for (const TestCase& test : tests) {
        const long long actual = calculateFare(test.zone, test.hour);
        const bool passed = actual == test.expectedFarePaise;
        allPassed = allPassed && passed;
        totalFarePaise += actual;

        std::cout << zoneName(test.zone) << "    "
                  << test.hour << ":00   ";
        printMoney(test.expectedFarePaise);
        std::cout << "   ";
        printMoney(actual);
        std::cout << "   " << (passed ? "PASS" : "FAIL") << '\n';
    }

    std::cout << "Total for five journeys: ";
    printMoney(totalFarePaise);
    std::cout << "\nAll fare tests passed: "
              << (allPassed ? "Yes" : "No") << "\n";

    // Check all specified peak-time boundaries.
    std::cout << "\nPeak boundary checks:\n";
    for (int hour : {8, 10, 17, 20}) {
        std::cout << hour << ":00 is "
                  << (isPeakTime(hour) ? "peak" : "off-peak") << '\n';
    }

    // Check that a balance leaving exactly Rs 50 is accepted.
    const long long exactBalance = 5'000 + 2'000; // Rs 70 balance, Rs 20 fare
    std::cout << "\nBalance leaving exactly Rs 50: "
              << (canTravel(exactBalance, 2'000) ? "accepted" : "denied")
              << '\n';

    // Invalid input checks.
    Zone parsedZone;
    int parsedHour;
    long long rechargePaise;

    std::cout << "Unknown zone (9): "
              << (parseZone("9", parsedZone) ? "accepted" : "rejected") << '\n';
    std::cout << "Negative recharge (-10): "
              << (parseRecharge("-10", rechargePaise) ? "accepted" : "rejected") << '\n';
    std::cout << "Letters for hour (abc): "
              << (parseHour("abc", parsedHour) ? "accepted" : "rejected") << '\n';

    return allPassed ? 0 : 1;
}
