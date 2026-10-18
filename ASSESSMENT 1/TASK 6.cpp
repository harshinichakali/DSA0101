#include <iostream>
#include <iomanip>

enum class Zone {
    Inner,
    Middle,
    Outer
};

constexpr long long BASE_FARE[] = {
    1000,  // Inner: Rs 10.00
    2000,  // Middle: Rs 20.00
    3000   // Outer: Rs 30.00
};

constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr long long MIN_BALANCE_PAISE = 5000; // Rs 50.00

long long fare(Zone zone, bool peak) {
    // Select the base fare for the farthest zone travelled.
    long long amount = 0;

    switch (zone) {
        case Zone::Inner:
            amount = BASE_FARE[0];
            break;
        case Zone::Middle:
            amount = BASE_FARE[1];
            break;
        case Zone::Outer:
            amount = BASE_FARE[2];
            break;
    }

    // Apply the peak surcharge using integer arithmetic.
    if (peak) {
        amount = amount * (100 + PEAK_SURCHARGE_PERCENT) / 100;
    }

    return amount;
}

bool canTravel(long long balance, long long fareAmount) {
    // Approve only if at least Rs 50 remains after payment.
    return balance - fareAmount >= MIN_BALANCE_PAISE;
}

int main() {
    long long balance = 10000; // Rs 100.00 in paise

    struct Trip {
        Zone zone;
        bool peak;
    };

    Trip trips[] = {
        {Zone::Inner,  false},
        {Zone::Outer,  true},
        {Zone::Middle, false}
    };

    for (const Trip& trip : trips) {
        const long long fareAmount = fare(trip.zone, trip.peak);

        if (canTravel(balance, fareAmount)) {
            balance -= fareAmount;

            std::cout << "Fare Rs "
                      << fareAmount / 100 << '.'
                      << std::setw(2) << std::setfill('0')
                      << fareAmount % 100
                      << " balance Rs "
                      << balance / 100 << '.'
                      << std::setw(2) << std::setfill('0')
                      << balance % 100 << '\n';
        } else {
            std::cout << "Denied (low balance) balance Rs "
                      << balance / 100 << '.'
                      << std::setw(2) << std::setfill('0')
                      << balance % 100 << '\n';
        }
    }

    return 0;
}
