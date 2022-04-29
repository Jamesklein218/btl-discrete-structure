#include "ex1a.h"
#include "ex1b.h"
#include "ex1c.h"

using namespace std;

int main()
{
    while (true)
    {
        string x;
        cout << ">> ";
        getline(cin, x);
        cout << endl;
        if (x == "q" || x == "quit" || x == "exit")
            break;

        try
        {
            string ex1b = infixToPostfix(x);
            string ex1a = infixToPrefix(x);
            double ex1c1 = calculate(ex1a, 0);
            double ex1c2 = calculate(ex1b, 1);
            cout << "Infix to POSTFIX: " << '"' << ex1b << '"' << endl;
            cout << "Infix to PREFIX:  " << '"' << ex1a << '"' << endl;
            cout << "Calculating postfix: " << ex1c2 << endl;
            cout << "Calculating prefix: " << ex1c1 << endl;
        }
        catch (char const *msg)
        {
            cout << "Error: " << msg << endl;
        }
        cout << endl;
    }
    return 0;
}
