#include "calculate.h"

Calculate::Calculate(QObject *parent) :
  QObject(parent),
  first_number("0"),
  second_number("0"),
  operation("0"),
  result("0"),
  is_operation_possible(false)
{
    operation_function["+"] = [](double a, double b) { return a + b; };
    operation_function["-"] = [](double a, double b) { return a - b; };
    operation_function["*"] = [](double a, double b) { return a * b; };
    operation_function["/"] = [](double a, double b) { return a / b; };
    operation_function["%"] = [](double a, double b) {
        if (a == static_cast<int>(a) && b == static_cast<int>(b))
            return (double)(static_cast<int>(a) % static_cast<int>(b));
        return -1.0;
    };
    operation_function["^"] = [](double a, double b) {
        if (a == static_cast<int>(a) && b == static_cast<int>(b))
            return (double)(pow(static_cast<int>(a), static_cast<int>(b)));
        return -1.0;
    };
}


void Calculate::addButton(QGridLayout *p_layout)
{
  QChar panel_symbols[] = { '1', '2', '3', 'C',
                            '4', '5', '6', '+',
                            '7', '8', '9', '-',
                            '0', '*', '/', '^',
                            '%', '.', '='};
  int row;
  int column;
  int sizeX = 200;
  int sizeY = 200;
  QSizePolicy::Policy horiz = QSizePolicy::Minimum;
  QSizePolicy::Policy vertical = QSizePolicy::Minimum;
  QPalette palette;
  QColor color;

  for(size_t i = 0; i < 19; ++i)
    {
       row = i / 4;
       column = i - row * 4;
       QPushButton *button = new QPushButton(panel_symbols[i]);

       if (panel_symbols[i] == '=') {
           p_layout->addWidget(button, row + 1, column, 1, 2);
           sizeX = sizeX << 1;
       }
       else {
           p_layout->addWidget(button, row + 1, column, 1, 1);
       }

       setColor(palette, color, *button, panel_symbols[i]);
       button->setMaximumSize(sizeX, sizeY);
       button->setSizePolicy(horiz, vertical);
       p_layout->setSpacing(0);
       p_layout->setMargin(0);
       QObject::connect(button, SIGNAL(clicked()),
                        this, SLOT(buttonClick()));

       button->setAutoFillBackground(true);
    }
}

void Calculate::buttonClick()
{
  QString input = ((QPushButton*)sender())->text();

  if (input <= '9' && input >= '0') {
    QString &cur_number = is_operation_possible ? second_number : first_number;
    addDigit(cur_number, input);
    result = cur_number;
  }
  else if (input == '=') {
    if (is_operation_possible) {
        if (operation == "/" && second_number == "0") {
            first_number = "";
            second_number = "";
            result = "Error!";
        }
        else {
            result = QString::number(operation_function[operation](first_number.toDouble(), second_number.toDouble()));
            is_operation_possible = false;
            first_number = result;
            second_number = "0";

            if ((operation == "%" || operation == "^") && result == "-1")
            {
                result = "Invalid operation!";
                first_number = "";
            }
        }
    }
  }
  else if (input == 'C') {
    result = "0";
    first_number = "";
    second_number = "";
    is_operation_possible = false;
  }
  else if (input == "."){
      if (is_operation_possible) {
          if (!second_number.contains("."))
              second_number.append(".");
          result = second_number;
      }
      else {
          if (!first_number.contains("."))
              first_number.append(".");
          result = first_number;
      }
      qDebug() << result;
  }
  else {
    //operations
    operation = input;
    is_operation_possible = true;
    result = second_number;
  }
  emit setNumber(result);
}

void Calculate::setColor(QPalette & palette, QColor & color, QPushButton & button, QChar symbol)
{
    int rgb_color_button[3];
    if (symbol.isNumber() || symbol == ".") {
        rgb_color_button[0] = rgb_color_button[1] = rgb_color_button[2] = 51;
    }
    else {
        rgb_color_button[0] = 235, rgb_color_button[1] = 132, rgb_color_button[2] = 53;
    }
    color.setRgb(rgb_color_button[0], rgb_color_button[1], rgb_color_button[2]);
    palette.setColor(QPalette::Button, color);
    color.setRgb(254, 254, 254);
    palette.setColor(QPalette::ButtonText, color);
    button.setPalette(palette);
}

void Calculate::addDigit(QString &number, const QString &input)
{
    if (number == "0")
        number = "";
    number.append(input);
}
