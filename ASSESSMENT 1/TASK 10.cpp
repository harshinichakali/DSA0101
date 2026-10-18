#include <iomanip>
#include <iostream>
#include <limits>

int main() {
    // Example assumption: every journey pays the maximum peak fare, Rs 36.
    // Change this value or use actual per-journey fares for your dataset.
    constexpr long long FARE_PAISE = 3'600;
    constexpr double FARE_RUPEES = 36.00;

    constexpr long long journeyCounts[] = {
        20'000, 500'000, 3'000'000
    };

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Fare per journey: Rs " << FARE_RUPEES << "\n\n";
    std::cout << "Journeys | Integer-paise total | Double-rupee total | Difference\n";

    for (long long count : journeyCounts) {
        // Use long long so the paise total cannot overflow at these counts.
        const long long totalPaise = count * FARE_PAISE;

        // Repeated addition demonstrates the double-based approach.
        double totalRupees = 0.0;
        for (long long i = 0; i < count; ++i) {
            totalRupees += FARE_RUPEES;
        }

        const double paiseTotalAsRupees =
            static_cast<double>(totalPaise) / 100.0;
        const double difference = totalRupees - paiseTotalAsRupees;

        std::cout << count << " | Rs "
                  << totalPaise / 100 << '.'
                  << (totalPaise % 100 < 10 ? "0" : "")
                  << totalPaise % 100
                  << " | Rs " << totalRupees
                  << " | Rs " << difference << '\n';
    }

    // Check whether storing the network total in a 32-bit int would overflow.
    constexpr long long networkJourneys = 3'000'000;
    constexpr long long networkTotalPaise = networkJourneys * FARE_PAISE;

    std::cout << "\nNetwork total in paise: " << networkTotalPaise << '\n';
    std::cout << "int maximum: " << std::numeric_limits<int>::max() << '\n';

    if (networkTotalPaise > std::numeric_limits<int>::max()) {
        std::cout << "The network total does not fit in int when stored as paise.\n";
    } else {
        std::cout << "The network total fits in int when stored as paise.\n";
    }

    // Demonstrate floating-point rounding with a small value that is not
    // represented exactly in binary. This is separate from the Rs 36 fare.
    double tenPaiseTotal = 0.0;
    for (int i = 0; i < 10; ++i) {
        tenPaiseTotal += 0.10;
    }

    std::cout << "\nFloating-point demonstration: 10 additions of Rs 0.10 = Rs "
              << std::setprecision(17) << tenPaiseTotal << '\n';
    std::cout << "Exact integer-paise total for the same additions: 100 paise\n";

    return 0;
}
