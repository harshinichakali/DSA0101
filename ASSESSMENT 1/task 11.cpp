#include <array>
#include <iostream>
#include <stdexcept>

class FareTable {
public:
    // Index is the number of zones travelled.
    static constexpr std::array<int, 6> faresInPaise{
        0,  // 0 zones
        1000, // 1 zone: ₹10
        1500, // 2 zones: ₹15
        2000, // 3 zones: ₹20
        2500, // 4 zones: ₹25
        3000  // 5 zones: ₹30
    };

    static int fareInPaise(int zonesTravelled) {
        if (zonesTravelled < 1 ||
            zonesTravelled >= static_cast<int>(faresInPaise.size())) {
            throw std::invalid_argument("Invalid number of zones");
        }

        return faresInPaise[zonesTravelled];
    }
};

class MetroJourney {
public:
    MetroJourney(int startZone, int endZone)
        : startZone_(startZone), endZone_(endZone) {
        if (startZone < 1 || endZone < 1) {
            throw std::invalid_argument("Zone numbers must be positive");
        }
    }

    int zonesTravelled() const {
        return startZone_ > endZone_
            ? startZone_ - endZone_
            : endZone_ - startZone_;
    }

    int fareInPaise() const {
        return FareTable::fareInPaise(zonesTravelled());
    }

private:
    int startZone_;
    int endZone_;
};

int main() {
    try {
        MetroJourney journey(1, 4);

        const int fare = journey.fareInPaise();
        std::cout << "Zones travelled: " << journey.zonesTravelled() << '\n';
        std::cout << "Fare: ₹" << fare / 100
                  << '.' << (fare % 100 < 10 ? "0" : "")
                  << fare % 100 << '\n';
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
