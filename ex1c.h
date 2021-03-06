#ifndef calculate_h
#define calculate_h

#include "helper.h"

double calculate(string input, bool isPostfix)
{
    if (input.size() >= 1)
    {
        if (isPostfix)
        {
            input = postfixToPrefix(input);
        }

        string tmp;
        stringstream stream(input);
        stack<char> operator_stack;
        stack<double> operand_stack;
        bool prevIsNum = 0;

        bool finish = 0;
        while (stream >> tmp)
        {
            if (isdigit(tmp[0]) || (tmp[0] == '-' && tmp.size() > 1))
            {
                operand_stack.push(stod(tmp));

                if (prevIsNum)
                {
                    while (operand_stack.size() >= 2 && !operator_stack.empty())
                    {
                        double y = operand_stack.top();
                        operand_stack.pop();
                        double x = operand_stack.top();
                        operand_stack.pop();
                        operand_stack.push(calExpression(x, operator_stack.top(), y));
                        operator_stack.pop();
                    }
                    finish = 1;
                }
                else
                    finish = 0;
                prevIsNum = 1;
            }
            else
            {
                finish = 0;
                prevIsNum = 0;
                operator_stack.push(tmp[0]);
            }
        }
        if (!operand_stack.empty())
            return operand_stack.top();
    }
    throw "Missing input";
}

#endif
