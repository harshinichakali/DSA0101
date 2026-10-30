
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

const int CAPACITY = 50;
const int TOTAL = 100000;

// ORIGINAL DESIGN: Array shifting
class OriginalHistory
{
    int transactions[CAPACITY];
    int count;
    long long shifts;

public:
    OriginalHistory()
    {
        count = 0;
        shifts = 0;
    }

    void addTransaction(int amount)
    {
        if (count < CAPACITY)
        {
            transactions[count++] = amount;
        }
        else
        {
            for (int i = 0; i < CAPACITY - 1; i++)
            {
                transactions[i] = transactions[i + 1];
                shifts++;
            }

            transactions[CAPACITY - 1] = amount;
        }
    }

    long long getShifts()
    {
        return shifts;
    }

    void display()
    {
        cout << "\nOriginal Last 5 Transactions:\n";

        for (int i = count - 5; i < count; i++)
            cout << transactions[i] << " ";

        cout << endl;
    }
};

// REDESIGNED: Circular Buffer
class CircularHistory
{
    int transactions[CAPACITY];
    int start;
    int count;
    long long writes;

public:
    CircularHistory()
    {
        start = 0;
        count = 0;
        writes = 0;
    }

    void addTransaction(int amount)
    {
        int index;

        if (count < CAPACITY)
        {
            index = (start + count) % CAPACITY;
            count++;
        }
        else
        {
            index = start;
            start = (start + 1) % CAPACITY;
        }

        transactions[index] = amount;
        writes++;
    }

    long long getWrites()
    {
        return writes;
    }

    void display()
    {
        cout << "\nCircular Buffer Last 5 Transactions:\n";

        for (int i = count - 5; i < count; i++)
        {
            int index = (start + i) % CAPACITY;
            cout << transactions[index] << " ";
        }

        cout << endl;
    }
};

int main()
{
    OriginalHistory original;
    CircularHistory redesigned;

    // Test original design
    auto start1 = high_resolution_clock::now();

    for (int i = 1; i <= TOTAL; i++)
        original.addTransaction(i);

    auto end1 = high_resolution_clock::now();

    // Test redesigned solution
    auto start2 = high_resolution_clock::now();

    for (int i = 1; i <= TOTAL; i++)
        redesigned.addTransaction(i);

    auto end2 = high_resolution_clock::now();

    auto time1 =
        duration_cast<microseconds>(end1 - start1).count();

    auto time2 =
        duration_cast<microseconds>(end2 - start2).count();

    cout << "ORIGINAL DESIGN\n";
    original.display();

    cout << "Total shifts: " << original.getShifts() << endl;
    cout << "Execution time: " << time1 << " microseconds\n";

    cout << "\nREDESIGNED SOLUTION\n";
    redesigned.display();

    cout << "Total writes: " << redesigned.getWrites() << endl;
    cout << "Execution time: " << time2 << " microseconds\n";

    return 0;
}
