
#include <iostream>
#include <cstdlib>
using namespace std;

class Time
{
    int h, m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}

    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

// TODO 1: Find absolute difference between two times
inline int minutesBetween(const Time& a, const Time& b)
{
    int time1 = a.h * 60 + a.m;
    int time2 = b.h * 60 + b.m;

    return abs(time1 - time2);
}

// TODO 2: Check whether time a is earlier than time b
inline bool earlier(const Time& a, const Time& b)
{
    if (a.h < b.h)
        return true;
    else if (a.h == b.h && a.m < b.m)
        return true;
    else
        return false;
}

int main()
{
    Time departure(9, 45);
    Time arrival(13, 10);

    cout << minutesBetween(departure, arrival) << " "
         << boolalpha << earlier(arrival, departure) << '\n';

    return 0;
}
