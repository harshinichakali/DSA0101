
#include <iostream>
#include <vector>
using namespace std;

// Return reference to highest mark
int& highestMark(int marks[], int n)
{
    int maxIndex = 0;

    for (int i = 1; i < n; i++)
    {
        if (marks[i] > marks[maxIndex])
            maxIndex = i;
    }

    return marks[maxIndex];
}

// Returning a reference to a local variable (DANGEROUS)
int& dangerousFunction()
{
    int x = 100;
    return x;  // Dangling reference - undefined behaviour
}

// Return const reference
const int& getHighest(const int marks[], int n)
{
    int maxIndex = 0;

    for (int i = 1; i < n; i++)
    {
        if (marks[i] > marks[maxIndex])
            maxIndex = i;
    }

    return marks[maxIndex];
}

// Return a copy
int getCopy(const int marks[], int n)
{
    int maxIndex = 0;

    for (int i = 1; i < n; i++)
    {
        if (marks[i] > marks[maxIndex])
            maxIndex = i;
    }

    return marks[maxIndex];
}

int main()
{
    int marks[] = {75, 85, 90, 80};
    int n = 4;

    cout << "Original highest mark: "
         << highestMark(marks, n) << endl;

    // Modify array element using reference
    highestMark(marks, n) += 2;

    cout << "After moderation: "
         << highestMark(marks, n) << endl;

    // Const reference
    cout << "Highest mark using const reference: "
         << getHighest(marks, n) << endl;

    // Returning a copy
    cout << "Highest mark using copy: "
         << getCopy(marks, n) << endl;

    // Growing vector example
    vector<int> v = {70, 80, 90};

    int* ptr = &v[2];

    v.push_back(100);

    cout << "Vector highest mark: " << v[3] << endl;

    cout << "Pointer obtained before vector growth may be invalid."
         << endl;

    return 0;
}
