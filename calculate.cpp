#include "calculate.h"

#include <exception>
#include <stdexcept>

Calculate::Calculate(QLabel *_label, QGridLayout *_grid_layout, QObject *parent) :
  QObject(parent),
  current_expression("0"),
  label(_label),
  grid_layout(_grid_layout)
{
    cb_expression = new QComboBox();
    operation_function["+"] = [](double a, double b) { return a + b; };
    operation_function["-"] = [](double a, double b) { return a - b; };
    operation_function["*"] = [](double a, double b) { return a * b; };
    operation_function["/"] = [](double a, double b) { return a / b; };
}


void Calculate::addButton()
{
  QChar panel_symbols[] = { '1', '2', '3', 'C',
                            '4', '5', '6', '+',
                            '7', '8', '9', '-',
                            '0', '.', '/', '*',
                            '(', ')', '='};
  int row;
  int column;
  int sizeX = 200;
  int sizeY = 200;
  QSizePolicy::Policy horiz = QSizePolicy::Minimum;
  QSizePolicy::Policy vertical = QSizePolicy::Minimum;
  grid_layout->addWidget(cb_expression, 2, 4, 1, 2);
  QObject::connect(cb_expression, SIGNAL(currentTextChanged(const QString &)),
                   label, SLOT(setText(const QString &)));

  for(size_t i = 0; i < 19; ++i)
    {
       row = i / 4;
       column = i - row * 4;
       QPushButton *button = new QPushButton(panel_symbols[i]);

       if (panel_symbols[i] != '=') {
           grid_layout->addWidget(button, row + 1, column, 1, 1);
       }
       else {
           grid_layout->addWidget(button, row + 1, column, 1, 2);
           sizeX = sizeX << 1;
       }

       setColor(*button, panel_symbols[i], true);
       button->setMaximumSize(sizeX, sizeY);
       button->setSizePolicy(horiz, vertical);
       grid_layout->setSpacing(0);
       grid_layout->setMargin(0);
       QObject::connect(button, SIGNAL(clicked()),
                        this, SLOT(buttonClick()));

       button->setAutoFillBackground(true);
       buttons.push_back(button);
    }
}

void Calculate::buttonClick()
{
  QString input = ((QPushButton*)sender())->text();
  double result;

  //добавить скобочки
    if (input <= '9' && input >= '0') {
        clickDigitButton(input);
    }
    else if (input == '=') {
        clickEqualButton(result);
    }
    else if (input == 'C') {
        current_expression = "0";
    }
    else if (input == "."){
      //если вводится . без числа то уведомляем пользователя что ввод некорректен
      //если число есть то проверяем есть ли в нем точка если есть игнорируем если нет то добавляем
      clickPointButton();
    }
    else {
      //operations
      //если знак вводится в пустую строку то ошибка уведомляем пользовотеля
      //если знак вводится после знака то ставим его вместо прошлого
      //после знака обязательно должно идти число
      clickOperationButton(input);
    }
    emit setNumber(current_expression);
}

void Calculate::setColor(QPushButton &button, QChar symbol, bool theme)
{
    QPalette palette;
    QColor color_button;
    QColor color_font;

    if (theme) {
        if (symbol.isNumber() || symbol == ".") {
            color_button.setRgb(51, 51, 51);
        }
        else {
            color_button.setRgb(235, 132, 53);
        }
        color_font.setRgb(254, 254, 254);
    }
    else {
        //white theme
        if (symbol.isNumber() || symbol == ".") {
            color_button.setRgb(255, 255, 255);
            color_font.setRgb(54, 54, 54);
        }
        else {
            color_button.setRgb(63, 81, 181);
            color_font.setRgb(254, 254, 254);
        }
    }

    palette.setColor(QPalette::Button, color_button);
    palette.setColor(QPalette::ButtonText, color_font);
    button.setPalette(palette);
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

bool Calculate::isOperation(const QChar &symbol) const
{
    if (symbol == "+" || symbol == "-" ||
        symbol == "*" || symbol == "/")
        return true;
    return false;
}

void Calculate::clickEqualButton(double &result)
{
    if (current_expression.contains("=")) {
        current_expression = current_expression.right(current_expression.size() - 1 - current_expression.lastIndexOf(QChar('=')));
    }
    else if (correctBracketSequence(label->text())) {
        //проверка на операнды
        QQueue<QString> expression = convert2ReversePolishNotation(label->text());
        result = calculate(expression);
        //добавляем пример в историю
        //history_expression.push_back(current_expression);
        cb_expression->addItem(current_expression);
        current_expression.append("=" + QString::number(result));
    }
    else {
        /*
         * скобочная последовательность не верна, извещаем пользователя об этом
        */
    }
}

void Calculate::clickPointButton()
{
    if (!current_expression.size() || isOperation(current_expression[current_expression.size() - 1])) {
        //введена точка после знака операции или в пустой строке - ошибка
        //ДОБАВИТЬ УВЕДОМЛЕНИЕ ПОЛЬЗОВАТЕЛЯ О ТОМ ЧТО ВВОД НЕКОРРЕКТЕН
    }
    else if (current_expression.contains(QRegExp("[0-9]*[.][0-9]*$"))) {
        //точка уже была введена
        //при вводе меняем ее местоположение
        int position = current_expression.lastIndexOf(QChar('.'));
        current_expression.remove(position, 1);
        current_expression.append(".");
    }
    else {
        //Если нет точек в числе то просто добавляем в конец
        current_expression.append(".");
    }
}

  void Calculate::clickDigitButton(const QString &input)
  {
      if (current_expression.back() == "0")
          current_expression = input;
      else
          current_expression.append(input);
  }

  void Calculate::clickOperationButton(const QString &input)
  {
      if (!current_expression.size()) {
          //ввели в пустую строку символ - ошибка
          //ДОБАВИТЬ УВЕДОМЛЕНИЕ ПОЛЬЗОВОТЕЛЯ ОБ ЭТОМ
      }
      else if (isOperation(current_expression[current_expression.size() - 1]) && isOperation(input[0])) {
          //Если стоял знак и мы ввели знак снова то он ставится на место прошлого
          current_expression[current_expression.size() - 1] = input[0]; //выполнить приведение к QChar
      }
      else{
          current_expression.append(input);
      }
  }


void Calculate::changeTheme(int flag)
{
    for (auto i : buttons)
    {
        setColor(*i, i->text()[0], flag);
    }
}
