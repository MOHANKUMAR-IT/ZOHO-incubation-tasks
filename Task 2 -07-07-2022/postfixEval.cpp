#include <bits/stdc++.h>

using namespace std;

int doProcess(string &exp)
{
    stack<char> stack;
    int i;

    for (i = 0; i<exp.size(); ++i)
    {
        if (isdigit(exp[i]))
            stack.push(exp[i] - '0');
        else
        {
            int val1 = stack.top();stack.pop();
            int val2 = stack.top();stack.pop();
            switch (exp[i])
            {
                case '+': stack.push(val2 + val1); break;
                case '-': stack.push(val2 - val1); break;
                case '*': stack.push(val2 * val1); break;
                case '/': stack.push(val2/val1); break;
            }
        }
    }
    return stack.top();
}

int main()
{
    string s = "25+3*83/-";
    cout<<"postfix evaluation: "<< doProcess(s);
    return 0;
}
