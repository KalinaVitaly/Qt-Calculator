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

class Calculate : public QObject
{
  Q_OBJECT
private:
  QString first_number;
  QString second_number;
  QString operation;
  QString result;
  QLabel *label;
  bool is_operation_possible;
  QMap<QString, std::function<int(int, int)>> operation_function;

  void addDigit(QString &number, const QString &input);
  void setColor(QPalette & palette, QColor & color, QPushButton & button, QChar symbol);

  bool correctBracketSequence(const QString &expression);
  int calculate(QQueue<QString>& expression);
  QQueue<QString> convert2ReversePolishNotation(const QString &expression);
public:
  explicit Calculate(QLabel *_label, QObject *parent = nullptr);

  void addButton(QGridLayout *p_layout);

signals:
  void setNumber(const QString &);
public slots:
  void buttonClick();
};

#endif // CALCULATE_H
