#include <iostream>
using namespace std;

int main()
{
    int i, x, y;

    cout << "SOURCE CODE OPTIMIZATION" << endl;

    // 1. Operator Strength Reduction
    cout << "\n1. Operator Strength Reduction" << endl;
    x = 5 * 2;
    cout << "Before Optimization: x = 5 * 2" << endl;
    x = 5 + 5;
    cout << "After Optimization:  x = 5 + 5" << endl;
    cout << "Value of x = " << x << endl;

    // 2. Dead Code Elimination
    cout << "\n2. Dead Code Elimination" << endl;
    x = 10;
    y = 20;
    x = 30;  // Previous assignment x = 10 is overwritten
    cout << "Before Optimization: x = 10; y = 20; x = 30;" << endl;
    cout << "After Optimization:  y = 20; x = 30;" << endl;
    cout << "Value of x = " << x << endl;

    // 3. Frequency Reduction
    cout << "\n3. Frequency Reduction" << endl;
    cout << "Before Optimization:" << endl;

    for (i = 0; i < 3; i++)
    {
        x = i * 10;
        cout << x << " ";
    }

    cout << "\nAfter Optimization:" << endl;

    // The multiplication factor is calculated outside the loop
    int factor = 10;

    for (i = 0; i < 3; i++)
    {
        x = i * factor;
        cout << x << " ";
    }

    cout << endl;
    return 0;
}
