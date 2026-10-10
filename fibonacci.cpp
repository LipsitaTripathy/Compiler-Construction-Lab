#include <iostream>
using namespace std;

int main()
{
    int n, first = 0, second = 1, next;

    cout << "Enter the number of terms: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Please enter a positive number of terms." << endl;
    }
    else
    {
        cout << "Fibonacci Series: ";

        for (int i = 1; i <= n; i++)
        {
            cout << first << " ";

            next = first + second;
            first = second;
            second = next;
        }

        cout << endl;
    }

    return 0;
}
