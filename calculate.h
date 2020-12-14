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
#include <QGridLayout>

class Calculate : public QObject
{
  Q_OBJECT
private:
  QString current_expression;
  QMap<QString, std::function<double(double, double)>> operation_function;

  void addDigit(QString &number, const QString &input);
  bool correctBracketSequence(const QString &expression);
  double calculate(QQueue<QString>& expression);
  QQueue<QString> convert2ReversePolishNotation(const QString &expression);

public:
  explicit Calculate(QObject *parent = nullptr);

signals:
  void setResult(const QString &expression);
public slots:
  void calculateExpression(const QString &expression);
};

#endif // CALCULATE_H
