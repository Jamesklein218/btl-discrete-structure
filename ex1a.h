#ifndef infixtoprefix_h
#define infixtoprefix_h

#include "ex1b.h"
#include "helper.h"

string postfixToPrefix(string postFix)
{
	stringstream pStream(postFix);
	string tmp;
	stack<string> pStack;

	while (pStream >> tmp)
	{
		if (isOperator(tmp[0]) && tmp.size() == 1)
		{
			string p1 = "", p2 = "";
			if (!pStack.empty())
			{
				p1 = pStack.top();
				pStack.pop();
			}

			if (!pStack.empty())
			{
				p2 = pStack.top();
				pStack.pop();
			}

			string construct = tmp + " " + p2 + " " + p1 + " ";
			pStack.push(construct);
		}
		else
		{
			pStack.push(tmp);
		}
	}

	tmp.clear();
	while (!pStack.empty())
	{
		tmp += pStack.top();
		pStack.pop();
	}

	return tmp;
}

// Main function
string infixToPrefix(string input)
{
	string postFix = infixToPostfix(input);
	return postfixToPrefix(postFix);
}

#endif
