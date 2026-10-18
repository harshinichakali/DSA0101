#include <iostream>

// Shared fare rule: Rs 50 must remain after the fare is deducted.
constexpr long long MINIMUM_BALANCE_PAISE = 5'000;

// ---------------- Procedural version ----------------

long long calculateFareProcedural(long long baseFarePaise, bool isPeak) {
    if (isPeak) {
        baseFarePaise = baseFarePaise * 120 / 100; // 20% surcharge
    }
    return baseFarePaise;
}

bool canTravelProcedural(long long balancePaise, long long farePaise) {
    return farePaise >= 0 &&
           balancePaise >= farePaise + MINIMUM_BALANCE_PAISE;
}

bool deductFareProcedural(long long& balancePaise, long long farePaise) {
    if (!canTravelProcedural(balancePaise, farePaise)) {
        return false;
    }

    balancePaise -= farePaise;
    return true;
}

// ---------------- Object-oriented version ----------------

class SmartCard {
private:
    long long balancePaise;

public:
    explicit SmartCard(long long startingBalancePaise)
        : balancePaise(startingBalancePaise >= 0
                           ? startingBalancePaise
                           : 0) {}

    bool canTravel(long long farePaise) const {
        return farePaise >= 0 &&
               balancePaise >= farePaise + MINIMUM_BALANCE_PAISE;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) {
            return false;
        }

        balancePaise -= farePaise;
        return true;
    }

    long long getBalance() const {
        return balancePaise;
    }
};

void printRupees(long long amountPaise) {
    std::cout << "Rs " << amountPaise / 100 << '.';
    const long long paise = amountPaise % 100;
    if (paise < 10) {
        std::cout << '0';
    }
    std::cout << paise;
}

int main() {
    constexpr long long BASE_FARE_PAISE = 3'000; // Rs 30.00
    constexpr bool IS_PEAK = true;

    const long long farePaise =
        calculateFareProcedural(BASE_FARE_PAISE, IS_PEAK);

    // Run the procedural version.
    long long proceduralBalancePaise = 10'000; // Rs 100.00

    std::cout << "Procedural version: ";
    if (deductFareProcedural(proceduralBalancePaise, farePaise)) {
        std::cout << "journey approved; balance ";
        printRupees(proceduralBalancePaise);
    } else {
        std::cout << "journey denied; balance ";
        printRupees(proceduralBalancePaise);
    }
    std::cout << '\n';

    // Run the object-oriented version.
    SmartCard card(10'000); // Rs 100.00

    std::cout << "Object-oriented version: ";
    if (card.deduct(farePaise)) {
        std::cout << "journey approved; balance ";
        printRupees(card.getBalance());
    } else {
        std::cout << "journey denied; balance ";
        printRupees(card.getBalance());
    }
    std::cout << '\n';

    return 0;
}
