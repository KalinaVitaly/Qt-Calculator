#include "calculate.h"

#include <exception>
#include <stdexcept>

Calculate::Calculate(QObject *parent) :
  QObject(parent),
  current_expression("0")
{
    operation_function["+"] = [](double a, double b) { return a + b; };
    operation_function["-"] = [](double a, double b) { return a - b; };
    operation_function["*"] = [](double a, double b) { return a * b; };
    operation_function["/"] = [](double a, double b) { return a / b; };
}

bool Calculate::correctBracketSequence(const QString &expression)
{
   int brackets = 0;
   for(auto i : expression)
   {
       if (i == "(")
           ++brackets;
       else if (i == ")") {
           --brackets;
           if (brackets < 0)
               return false;
       }
   }
   return true;
}

QQueue<QString> Calculate::convert2ReversePolishNotation(const QString &expression)
{
    QStack<QString> st;
    QQueue<QString> q;
    QMap<QString, int> priority_operation;
    QString current_number("");
    bool is_digits_successively = false;
    priority_operation["+"] = 1;
    priority_operation["-"] = 1;
    priority_operation["*"] = 2;
    priority_operation["/"] = 2;

    for (QChar i : expression)
    {
        if (i.isNumber() || i == ".")
        {
            current_number.append(i);
            if(is_digits_successively) {
                q.pop_back();
            }
            else {
                is_digits_successively = true;
            }
            q.push_back(current_number);
        }
        else
        {
            if (i == '(')
            {
                st.push(i);
            }
            else if (i == ')')
            {
                while(st.top() != '(')
                {
                    q.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }
            else
            {
                if(st.empty() || st.top() == '(' || priority_operation[st.top()] < priority_operation[i])
                {
                    st.push(i);
                }
                else
                {
                    while(priority_operation[st.top()] >= priority_operation[i] && st.top() != '(')
                    {
                        q.push_back(st.top());
                        st.pop();

                        if (st.empty())
                            break;
                    }
                    st.push(i);
                }
            }
            is_digits_successively = false;
            current_number = "";
        }
    }

    while(!st.empty())
    {
        q.push_back(st.top());
        st.pop();
    }
    return q;
}

double Calculate::calculate(QQueue<QString>& expression)
{
    QStack<double> numbers;
    double number1;
    double number2;
    auto oper_stack = [&numbers](double &number) {
        number = numbers.top();
        numbers.pop();
    };

    while(!expression.empty())
    {
        if ((expression.front().contains(QRegExp("\\d+")))) {
            numbers.push((expression.front()).toDouble());
        }
        else {
            oper_stack(number2);
            oper_stack(number1);
            try {
                double result = (operation_function[expression.front()](number1, number2));
                numbers.push(result);
            } catch (std::exception &ex) {
                qDebug() << ex.what();
            }
        }
        expression.pop_front();
    }
    return numbers.top();
}
