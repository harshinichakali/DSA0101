#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// Counter class
class Counter {
public:
    int v;

    Counter(int x = 0) {
        v = x;
    }

    // Prefix increment
    Counter& operator++() {
        ++v;
        return *this;
    }

    // Postfix increment
    Counter operator++(int) {
        Counter old = *this;
        v++;
        return old;
    }
};

// Time class
class Time {
public:
    int hour, minute, second;

    Time(int h = 0, int m = 0, int s = 0) {
        hour = h;
        minute = m;
        second = s;
    }

    // Prefix increment
    Time& operator++() {
        second++;

        if (second == 60) {
            second = 0;
            minute++;
        }

        if (minute == 60) {
            minute = 0;
            hour++;
        }

        if (hour == 24)
            hour = 0;

        return *this;
    }

    // Postfix increment
    Time operator++(int) {
        Time old = *this;
        ++(*this);
        return old;
    }

    // Equality operator
    bool operator==(const Time& t) const {
        return hour == t.hour &&
               minute == t.minute &&
               second == t.second;
    }

    // Not equal operator
    bool operator!=(const Time& t) const {
        return !(*this == t);
    }

    void display() const {
        cout << hour << ":"
             << minute << ":"
             << second << endl;
    }
};

// Playlist class
class Playlist {
    vector<string> tracks;

public:
    Playlist(vector<string> t) {
        tracks = t;
    }

    // Non-const subscript operator
    string& operator[](int index) {
        return tracks.at(index);
    }

    // Const subscript operator
    const string& operator[](int index) const {
        return tracks.at(index);
    }

    int size() const {
        return tracks.size();
    }
};

int main() {

    // Counter demonstration
    Counter c(5);

    Counter a = c++;
    Counter b = ++c;

    cout << a.v << " "
         << b.v << " "
         << c.v << endl;

    // Time demonstration
    Time t(12, 30, 59);

    cout << "Postfix: ";
    (t++).display();

    cout << "Prefix: ";
    (++t).display();

    Time t2(12, 31, 1);

    cout << boolalpha;
    cout << "Equal: " << (t == t2) << endl;
    cout << "Not Equal: " << (t != t2) << endl;

    // Playlist demonstration
    Playlist p({"Song A", "Song B", "Song C"});

    cout << "Playlist:" << endl;

    for (int i = 0; i < p.size(); i++) {
        cout << p[i] << endl;
    }

    // Change a track using non-const operator
    p[1] = "New Song";

    cout << "Updated Track: " << p[1] << endl;

    // Range checking
    try {
        cout << p[5] << endl;
    }
    catch (const out_of_range& e) {
        cout << "Invalid track index!" << endl;
    }

    return 0;
}
