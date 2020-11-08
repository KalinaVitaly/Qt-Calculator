#ifndef CALCULATE_H
#define CALCULATE_H

#include <QObject>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QMap>
#include <cmath>
#include <QStack>
#include <QQueue>
#include <QComboBox>
#include <QCheckBox>

class Calculate : public QObject
{
  Q_OBJECT
private:
  QString current_expression;
  QLabel *label;
  QMap<QString, std::function<double(double, double)>> operation_function;
  QStringList history_expression;
  QVector<QPushButton *> buttons;      //указатели на кнопки

  void addDigit(QString &number, const QString &input);
  void setColor(QPushButton &button, QChar symbol, bool theme);
  bool correctBracketSequence(const QString &expression);
  bool isOperation(const QChar &symbol) const;
  double calculate(QQueue<QString>& expression);
  QQueue<QString> convert2ReversePolishNotation(const QString &expression);
  void clickEqualButton(double &result);
  void clickPointButton();
  void clickDigitButton(const QString &input);
  void clickOperationButton(const QString &input);
public:
  explicit Calculate(QLabel *_label, QObject *parent = nullptr);

  void addButton(QGridLayout *p_layout);

signals:
  void setNumber(const QString &);
public slots:
  void buttonClick();
  void changeTheme(int flag);
};

#endif // CALCULATE_H
