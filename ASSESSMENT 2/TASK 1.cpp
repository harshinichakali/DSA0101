#include <iostream>
using namespace std;

int main() {
    int startZone, endZone, zones, fare;

    cin >> startZone >> endZone;

    zones = abs(endZone - startZone);

    switch (zones) {
        case 1: fare = 10; break;
        case 2: fare = 15; break;
        case 3: fare = 20; break;
        case 4: fare = 25; break;
        case 5: fare = 30; break;
        default:
            cout << "Invalid number of zones";
            return 0;
    }

    cout << "Zones travelled: " << zones << endl;
    cout << "Fare: Rs." << fare << ".00" << endl;

    return 0;
}
