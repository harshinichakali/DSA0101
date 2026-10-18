#include <iostream>

constexpr bool isPeakHour(int hour) {
    // Peak intervals: [08:00, 10:00) and [17:00, 20:00).
    return (hour >= 8 && hour < 10) ||
           (hour >= 17 && hour < 20);
}

constexpr int applyPeakSurcharge(int fare, bool peak) {
    // Assumes fares and surcharge calculations are in whole rupees.
    return peak ? fare * 120 / 100 : fare;
}

constexpr int applyConcession(int fare, bool eligible) {
    // Assumption: concession is 50%, applied after the peak surcharge.
    return eligible ? fare / 2 : fare;
}

int main() {
    int x = 5;
    int y = 3;

    std::cout << x + y * 2 << ' ' << (x + y) * 2 << '\n';

    int z = x++ + ++y;
    std::cout << z << ' ' << x << ' ' << y << '\n';

    std::cout << (x > y ? x : y) << ' ' << x % 4 * 2 << '\n';
    std::cout << 10 / 3 << ' ' << 10 % 3 << ' '
              << -10 / 3 << ' ' << -10 % 3 << '\n';

    int k = 0;
    for (int i = 0; i < 10; i += 3)
        k += i;

    std::cout << k << '\n';

    int hour = 8;
    int baseFare = 30;
    bool concessionEligible = true;

    const bool peak = isPeakHour(hour);
    const int fareAfterSurcharge = applyPeakSurcharge(baseFare, peak);
    const int finalFare = applyConcession(
        fareAfterSurcharge, concessionEligible);

    std::cout << "Peak: " << std::boolalpha << peak
              << ", fare: Rs " << finalFare << '\n';

    return 0;
}
