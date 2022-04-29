#ifndef INFIXTOPOSTFIX
#define INFIXTOPOSTFIX

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <math.h>

using namespace std;

// Helper functions
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
			parenthesis.pop();
		}
		// Check valid digit
		else if (!isdigit(input[i]) && !isOperator(input[i]) && input[i] != ' ' && input[i] != '.')
		{
			invalidChar = 1;
			break;
		}
	}

	if (!parenthesis.empty() || invalidChar)
		throw "Syntax error";
}

// Main function
string infixToPostfix(string input)
{
	checkSyntaxError(input);
	input = '(' + input + ')';
	stack<char> operator_stack;
	string res;
	string num = "";

	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == ' ')
			continue;
		else if (isdigit(input[i]) || input[i] == '.')
		{
			num += input[i];
		}
		else
		{
			if (!num.empty())
			{
				res += num;
				res += ' ';
				num.clear();
			}

			if (input[i] == '(')
			{
				operator_stack.push('(');
			}
			else if (input[i] == ')')
			{
				while (operator_stack.top() != '(')
				{
					res += operator_stack.top();
					res += ' ';
					operator_stack.pop();
				}

				operator_stack.pop();
			}
			else
			{
				while (getPriority(input[i]) <= getPriority(operator_stack.top()))
				{
					if (getPriority(input[i]) == getPriority(operator_stack.top()))
						throw "multiple-output error";

					res += operator_stack.top();
					res += ' ';
					operator_stack.pop();
				}
				operator_stack.push(input[i]);
			}
		}
	}

	while (!operator_stack.empty())
	{
		res += operator_stack.top();
		res += " ";
		operator_stack.pop();
	}

	if (res.size() >= 1)
		res.pop_back();

	return res;
}

#endif
