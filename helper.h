#ifndef helper_h
#define helper_h

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <math.h>

using namespace std;

bool isOperator(char c)
{
    if (
        c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '/' ||
        c == '^')
    {
        return true;
    }

    return false;
}

int getPriority(char c)
{
    if (c == '-' || c == '+')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    return 0;
}

string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

double calExpression(double x, char op, double y)
{
    switch (op)
    {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        if (y == 0)
            throw "Divided-by-0 error";
        return x / y;
    case '^':
        if (x == 0 && y == 0)
            throw "undefined";
        return pow(x, y);
    }

    throw "Syntax error";
}

void checkSyntaxError(string input)
{
    stack<char> parenthesis;
    bool spacing = 0;
    bool invalidChar = 0;
    bool isNum = 0, isSpaced = 0, isDotted = 0;

    for (int i = 0; i < input.size() && !invalidChar; ++i)
    {
        // Check spacing and floating point
        if (isdigit(input[i]) || input[i] == '.')
        {
            if (input[i] == '.' && (isDotted || !isNum))
                invalidChar = 1;
            if (input[i] == '.' && !isDotted)
                isDotted = 1;
            if (isNum && isSpaced)
                invalidChar = 1;
            isNum = 1;
            isSpaced = 0;
        }
        else if (input[i] == ' ')
            isSpaced = 1;
        else
        {
            isDotted = 0;
            isNum = 0;
            isSpaced = 0;
        }

        // Check parenthensis
        if (input[i] == '(')
            parenthesis.push(input[i]);
        else if (input[i] == ')')
        {
            if (parenthesis.empty())
                invalidChar = 1;
            else
                parenthesis.pop();
        }
        // Check valid digit
        else if (!isdigit(input[i]) && !isOperator(input[i]) && input[i] != ' ' && input[i] != '.')
        {
            invalidChar = 1;
            break;
        }
        cout << input[i] << endl;
    }

    if (!parenthesis.empty() || invalidChar)
        throw "Syntax error";
}

#endif
