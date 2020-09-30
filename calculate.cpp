#include "calculate.h"

Calculate::Calculate(QObject *parent) :
  QObject(parent),
  first_number(0),
  second_number(0),
  result(0),
  is_operation_possible(false),
  operation('0')
{
    operation_function["+"] = [](double a, double b) { return a + b; };
    operation_function["-"] = [](double a, double b) { return a - b; };
    operation_function["*"] = [](double a, double b) { return a * b; };
    operation_function["/"] = [](double a, double b) { return a / b; };
}


void Calculate::addButton(QGridLayout *p_layout)
{
  QChar panel_symbols[] = { '1', '2', '3', '+',
                            '4', '5', '6', '-',
                            '7', '8', '9', 'C',
                            '0', '*', '/', '=' };
  int row;
  int column;
  for(size_t i = 0; i < 16; ++i)
    {
       row = i / 4;
       column = i - row * 4;
       QPushButton *button = new QPushButton(panel_symbols[i]);
       button->setMaximumSize(200, 200);
       button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
       p_layout->addWidget(button, row + 1, column);
       p_layout->setSpacing(0);
       p_layout->setMargin(0);
       QObject::connect(button, SIGNAL(clicked()),
                        this, SLOT(buttonClick()));
    }
}

void Calculate::buttonClick()
{
  QString input = ((QPushButton*)sender())->text();

  if (input <= '9' && input >= '0') {
    if (is_operation_possible) {
        second_number = second_number * 10 + input.toDouble();
        emit setNumber(QString::number(second_number));
    }
    else {
        first_number = first_number * 10 + input.toDouble();
        emit setNumber(QString::number(first_number));
    }
  }
  else if (input == '=') {
    if (is_operation_possible) {
        result = operation_function[operation](first_number, second_number);
        is_operation_possible = false;
        first_number = result;
        second_number = 0;
        emit setNumber(QString::number(result));
    }
    else
        emit setNumber(QString::number(first_number));
  }
  else if (input == 'C') {
    result = 0;
    first_number = 0;
    second_number = 0;
    is_operation_possible = false;
    emit setNumber(QString::number(first_number));
  }
  else {
    //operations
    operation = input;
    is_operation_possible = true;
    emit setNumber(QString::number(second_number));
  }
}
