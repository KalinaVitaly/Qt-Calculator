#include "ButtonsWidget.h"

ButtonsWidget::ButtonsWidget(QWidget * parent) :
    QWidget(parent),
    panel_symbols(19)
{
    gl_buttons = new QGridLayout(this);
    panel_symbols = { '1', '2', '3', 'C',
                      '4', '5', '6', '+',
                      '7', '8', '9', '-',
                      '0', '.', '/', '*',
                      '(', ')', '='};
    setButtonsParams();
    this->setFixedSize(QSize(350, 400));
}

void ButtonsWidget::clickEqualButton(double &result)
{
    if (current_expression.contains("=")) {
        current_expression = current_expression.right(current_expression.size() - 1 - current_expression.lastIndexOf(QChar('=')));
    }
    //    else if (correctBracketSequence(label->text())) {
    //        //проверка на операнды
    //        QQueue<QString> expression = convert2ReversePolishNotation(label->text());
    //        result = calculate(expression);
    //        //добавляем пример в историю
    //        //history_expression.push_back(current_expression);
    //        cb_expression->addItem(current_expression);
    //        current_expression.append("=" + QString::number(result));
    //    }
    else {
        /*
         * скобочная последовательность не верна, извещаем пользователя об этом
        */
    }
}

bool ButtonsWidget::isOperation(const QChar &symbol) const
{
    if (symbol == "+" || symbol == "-" ||
        symbol == "*" || symbol == "/")
        return true;
    return false;
}

void ButtonsWidget::clickPointButton()
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

void ButtonsWidget::clickDigitButton(const QString &input) {
    if (current_expression.back() == "0")
        current_expression = input;
    else
        current_expression.append(input);
}

void ButtonsWidget::clickOperationButton(const QString &input) {
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


void ButtonsWidget::buttonClick()
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

void ButtonsWidget::setButtonsParams() {
    int row;
    int column;
    int sizeX = 200;
    int sizeY = 200;
    QSizePolicy::Policy horiz = QSizePolicy::Minimum;
    QSizePolicy::Policy vertical = QSizePolicy::Minimum;

    for(size_t i = 0; i < 19; ++i)
      {
         row = i / 4;
         column = i - row * 4;
         QPushButton *button = new QPushButton(panel_symbols[i]);

         if (panel_symbols[i] != '=') {
             gl_buttons->addWidget(button, row + 1, column, 1, 1);
         }
         else {
             gl_buttons->addWidget(button, row + 1, column, 1, 2);
             sizeX = sizeX << 1;
         }

         setButtonColor(*button, panel_symbols[i], true);
         button->setMaximumSize(sizeX, sizeY);
         button->setSizePolicy(horiz, vertical);
         gl_buttons->setSpacing(0);
         gl_buttons->setMargin(0);

         QObject::connect(button, SIGNAL(clicked()),
                          this, SLOT(buttonClick()));

         button->setAutoFillBackground(true);
         buttons.push_back(button);
      }
}

void ButtonsWidget::setButtonColor(QPushButton &button, QChar symbol, bool theme)
{
    if (symbol.isNumber()) {
        button.setStyleSheet("QPushButton {"\
                             "border : 1px solid gray;"\
                             "font-size : 20px;"\
                             "}"\
                             "QPushButton:pressed {"\
                             "background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"\
                             "stop : 0 #dadbde, stop: 1 #f6f7fa);"\
                             "}");
    }
    else {
        button.setStyleSheet("QPushButton {"\
                             "background-color : rgb(255, 151, 57);"\
                             "color : white;"\
                             "border : 1px solid gray;"\
                             "font-size : 20px;"\
                             "}"\
                             "QPushButton:pressed {"\
                             "background-color : qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"\
                             "stop : 0 #BEBEBE, stop: 1 #D7C7D7);"\
                             "}");
    }
}
