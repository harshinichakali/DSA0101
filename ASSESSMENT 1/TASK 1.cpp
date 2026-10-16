#include <iostream>
#include <string>
using namespace std;

// Amounts are stored as whole rupees to avoid floating-point fare errors.
enum class Zone {
    Inner = 1,
    Middle = 2,
    Outer = 3
};

class FareTable {
public:
    static constexpr int INNER_FARE = 10;
    static constexpr int MIDDLE_FARE = 20;
    static constexpr int OUTER_FARE = 30;
    static constexpr int PEAK_SURCHARGE_PERCENT = 20;
    static constexpr int MINIMUM_REMAINING_BALANCE = 50;

    static int baseFare(Zone farthestZone) {
        switch (farthestZone) {
            case Zone::Inner:  return INNER_FARE;
            case Zone::Middle: return MIDDLE_FARE;
            case Zone::Outer:  return OUTER_FARE;
        }
        return 0; // Defensive fallback for an invalid zone value.
    }

    // Peak periods are [08:00, 10:00) and [17:00, 20:00).
    static bool isPeakTime(int hour, int minute) {
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
            return false;

        const int time = hour * 60 + minute;
        const int morningStart = 8 * 60;
        const int morningEnd   = 10 * 60;
        const int eveningStart = 17 * 60;
        const int eveningEnd   = 20 * 60;

        return (time >= morningStart && time < morningEnd) ||
               (time >= eveningStart && time < eveningEnd);
    }

    static int journeyFare(Zone farthestZone, bool peak, bool eligibleForConcession) {
        int fare = baseFare(farthestZone);

        // Apply a 20% surcharge using integer arithmetic.
        if (peak)
            fare = fare * (100 + PEAK_SURCHARGE_PERCENT) / 100;

        // Assumption: concession is 50% of the fare, applied after peak surcharge.
        if (eligibleForConcession)
            fare /= 2;

        return fare;
    }
};

class SmartCard {
private:
    string cardId;
    int balance; // Whole rupees; never allowed to become negative.

public:
    SmartCard(const string& id, int startingBalance)
        : cardId(id), balance(startingBalance >= 0 ? startingBalance : 0) {}

    bool payFare(int fare) {
        if (fare < 0 || balance - fare < FareTable::MINIMUM_REMAINING_BALANCE)
            return false;

        balance -= fare;
        return true;
    }

    int getBalance() const { return balance; }
    string getCardId() const { return cardId; }
};

class Passenger {
private:
    string name;
    bool concessionEligible;

public:
    Passenger(const string& passengerName, bool eligible)
        : name(passengerName), concessionEligible(eligible) {}

    bool hasConcession() const { return concessionEligible; }
    string getName() const { return name; }
};

class Journey {
private:
    Passenger passenger;
    SmartCard& card;
    Zone farthestZone;
    int hour;
    int minute;

public:
    Journey(const Passenger& p, SmartCard& c, Zone zone, int h, int m)
        : passenger(p), card(c), farthestZone(zone), hour(h), minute(m) {}

    void process() const {
        const bool peak = FareTable::isPeakTime(hour, minute);
        const int fare = FareTable::journeyFare(
            farthestZone, peak, passenger.hasConcession());

        cout << "Passenger: " << passenger.getName() << '\n'
             << "Fare: Rs " << fare << '\n';

        if (card.payFare(fare)) {
            cout << "Journey approved. Remaining balance: Rs "
                 << card.getBalance() << '\n';
        } else {
            cout << "Journey denied. Card must retain at least Rs "
                 << FareTable::MINIMUM_REMAINING_BALANCE
                 << " after payment. Balance: Rs "
                 << card.getBalance() << '\n';
        }
    }
};

int main() {
    SmartCard card("CARD-1001", 100);
    Passenger passenger("Asha", true);

    // Example: Outer-zone journey at 8:30 AM, peak time.
    Journey journey(passenger, card, Zone::Outer, 8, 30);
    journey.process();

    return 0;
}
