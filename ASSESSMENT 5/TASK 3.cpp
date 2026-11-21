#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Bill Class
class Bill {
public:
    string treatment;
    double amount;

    Bill(string t, double a) {
        treatment = t;
        amount = a;
    }
};

// Abstract Base Class
class Player {
public:
    virtual double amountCovered(const Bill& b) = 0;
    virtual ~Player() {}
};

// Derived Class: SelfPay
class SelfPay : public Player {
public:
    double amountCovered(const Bill& b) override {
        return b.amount;
    }
};

// Derived Class: Insurance
class Insurance : public Player {
private:
    double coverLimit;
    double coPayment;

public:
    Insurance(double limit, double percentage) {
        coverLimit = limit;
        coPayment = percentage;
    }

    double amountCovered(const Bill& b) override {
        double eligibleAmount = b.amount * (1 - coPayment / 100.0);
        return min(eligibleAmount, coverLimit);
    }
};

// Derived Class: Government Scheme
class GovernmentScheme : public Player {
public:
    double amountCovered(const Bill& b) override {
        if (b.treatment == "Surgery")
            return 10000;
        else if (b.treatment == "Consultation")
            return 500;
        else if (b.treatment == "Scan")
            return 2000;
        else
            return 0;
    }
};

// Derived Class: Corporate Payer
class CorporatePayer : public Player {
private:
    double percentage;

public:
    CorporatePayer(double p) {
        percentage = p;
    }

    double amountCovered(const Bill& b) override {
        return b.amount * percentage / 100.0;
    }
};

int main() {
    Bill b1("Surgery", 15000);
    Bill b2("Consultation", 1000);
    Bill b3("Scan", 4000);

    vector<Player*> players;

    SelfPay self;
    Insurance insurance(8000, 20);
    GovernmentScheme govt;
    CorporatePayer corporate(75);

    players.push_back(&self);
    players.push_back(&insurance);
    players.push_back(&govt);
    players.push_back(&corporate);

    Bill bills[] = {b1, b2, b3};

    cout << "----- Healthcare Bill Coverage -----" << endl;

    for (int i = 0; i < 3; i++) {
        cout << "\nTreatment: " << bills[i].treatment << endl;

        for (Player* p : players) {
            cout << "Covered Amount: Rs. "
                 << p->amountCovered(bills[i]) << endl;
        }
    }

    return 0;
}
