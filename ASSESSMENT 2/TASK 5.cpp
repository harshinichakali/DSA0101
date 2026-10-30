
#include <iostream>
using namespace std;

class Ticket
{
    static int next;
    int id;

public:
    Ticket()
    {
        id = ++next;
    }

    int get() const
    {
        return id;
    }

    static int issued()
    {
        return next - 100;
    }
};

int Ticket::next = 100;

int main()
{
    Ticket counter[3];
    Ticket extra;

    cout << counter[0].get() << " "
         << counter[2].get() << " "
         << extra.get() << " "
         << Ticket::issued() << endl;

    return 0;
}
