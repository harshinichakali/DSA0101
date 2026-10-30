
#include <iostream>
using namespace std;

class SavingsAccount
{
private:
    int accountNumber;
    double balance;
    double transactions[10];
    int count;

public:
    // Constructor
    SavingsAccount(int accNo, double bal)
    {
        accountNumber = accNo;
        balance = bal;
        count = 0;
    }

    // Function defined inside the class
    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            addTransaction(amount);
            cout << "Amount deposited: " << amount << endl;
        }
        else
            cout << "Invalid deposit amount" << endl;
    }

    // Function defined outside the class
    void withdraw(double amount);

    void addTransaction(double amount);

    void miniStatement();
};

// Add transaction and discard oldest if full
void SavingsAccount::addTransaction(double amount)
{
    if (count < 10)
    {
        transactions[count] = amount;
        count++;
    }
    else
    {
        for (int i = 0; i < 9; i++)
        {
            transactions[i] = transactions[i + 1];
        }

        transactions[9] = amount;
    }
}

// Withdraw function
void SavingsAccount::withdraw(double amount)
{
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;
        addTransaction(-amount);
        cout << "Amount withdrawn: " << amount << endl;
    }
    else
    {
        cout << "Insufficient balance or invalid amount"
             << endl;
    }
}

// Display mini statement
void SavingsAccount::miniStatement()
{
    cout << "\n----- MINI STATEMENT -----" << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Available Balance: " << balance << endl;

    cout << "Last " << count << " Transactions:" << endl;

    for (int i = 0; i < count; i++)
    {
        cout << transactions[i] << endl;
    }

    cout << "--------------------------" << endl;
}

int main()
{
    SavingsAccount account(123456, 5000);

    account.deposit(1000);
    account.withdraw(500);
    account.deposit(2000);
    account.withdraw(300);
    account.deposit(1500);
    account.withdraw(200);
    account.deposit(800);
    account.withdraw(100);
    account.deposit(700);
    account.withdraw(400);
    account.deposit(1200);

    account.miniStatement();

    return 0;
}
