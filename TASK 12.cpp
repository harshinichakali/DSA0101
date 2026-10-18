#include <array>
#include <iomanip>
#include <iostream>
#include <stdexcept>

enum class DayType {
    Weekday,
    Weekend
};

enum class TimeType {
    OffPeak,
    Peak
};

class MonthlyPass {
public:
    MonthlyPass(int firstZone, int secondZone)
        : firstZone_(firstZone), secondZone_(secondZone) {
        validateZone(firstZone);
        validateZone(secondZone);

        if (firstZone == secondZone) {
            throw std::invalid_argument("Choose two different zones.");
        }
    }

    bool covers(int startZone, int endZone) const {
        return includes(startZone) && includes(endZone);
    }

private:
    int firstZone_;
    int secondZone_;

    bool includes(int zone) const {
        return zone == firstZone_ || zone == secondZone_;
    }

    static void validateZone(int zone) {
        if (zone < 1 || zone > 4) {
            throw std::invalid_argument("Zone must be between 1 and 4.");
        }
    }
};

class FareCalculator {
public:
    // Fare for a journey crossing this many zone boundaries, in paise.
    static constexpr std::array<int, 4> baseFarePaise{
        1000, // 1 zone boundary: ₹10
        1500, // 2 boundaries: ₹15
        2000, // 3 boundaries: ₹20
        2500  // 4 boundaries: ₹25
    };

    static constexpr int peakSurchargePercent = 20;
    static constexpr int weekendDiscountPercent = 10;

    static int calculate(int startZone,
                         int endZone,
                         DayType day,
                         TimeType time,
                         const MonthlyPass* pass = nullptr) {
        validateZone(startZone);
        validateZone(endZone);

        if (startZone == endZone) {
            return 0;
        }

        // The pass covers trips whose start and end zones are both selected.
        if (pass != nullptr && pass->covers(startZone, endZone)) {
            return 0;
        }

        const int boundaries = distance(startZone, endZone);
        int fare = baseFarePaise[boundaries - 1];

        // Weekend discount takes priority; it does not combine with peak surcharge.
        if (day == DayType::Weekend) {
            fare = fare * (100 - weekendDiscountPercent) / 100;
        } else if (time == TimeType::Peak) {
            fare = fare * (100 + peakSurchargePercent) / 100;
        }

        return fare;
    }

private:
    static int distance(int a, int b) {
        return (a > b) ? a - b : b - a;
    }

    static void validateZone(int zone) {
        if (zone < 1 || zone > 4) {
            throw std::invalid_argument("Zone must be between 1 and 4.");
        }
    }
};

int main() {
    try {
        MonthlyPass pass(1, 2); // Unlimited travel between these two zones.

        const int fare1 = FareCalculator::calculate(
            1, 4, DayType::Weekend, TimeType::Peak);
        const int fare2 = FareCalculator::calculate(
            1, 2, DayType::Weekday, TimeType::Peak, &pass);
        const int fare3 = FareCalculator::calculate(
            1, 3, DayType::Weekday, TimeType::Peak);

        std::cout << "Zone 1 to 4, weekend: ₹"
                  << std::fixed << std::setprecision(2) << fare1 / 100.0
                  << '\n';

        std::cout << "Zone 1 to 2, covered by pass: ₹"
                  << fare2 / 100.0 << '\n';

        std::cout << "Zone 1 to 3, weekday peak: ₹"
                  << fare3 / 100.0 << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
