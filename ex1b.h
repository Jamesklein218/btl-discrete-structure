#ifndef infixtopostfix_h
#define infixtopostfix_h

#include "helper.h"

string infixToPostfix(string input)
{
	checkSyntaxError(input);
	input = '(' + input + ')';
	input = removeSpaces(input);
	stack<char> operator_stack;
	string res;
	string num = "";

	for (int i = 0; i < input.size(); ++i)
	{
		if (isdigit(input[i]) || input[i] == '.')
		{
			num += input[i];
		}
		else
		{
			if (!num.empty() && num != "-")
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
				if ((i - 1 > 0 && !isdigit(input[i - 1]) &&
					 input[i - 1] != ')' && input[i - 1] != ' ') ||
					i - 1 == 0)
				{
					if (input[i] == '+')
						continue;
					if (input[i] == '-')
					{
						if (num.empty())
							num += input[i];
						else
							num.pop_back();
						continue;
					}
					else
						throw "undefined";
				}
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
