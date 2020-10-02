#ifndef CALCULATE_H
#define CALCULATE_H

#include <QObject>
#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QMap>
#include <cmath>

class Calculate : public QObject
{
  Q_OBJECT
private:
  QString first_number;
  QString second_number;
  QString operation;
  QString result;
  bool is_operation_possible;
  QMap<QString, std::function<double(double, double)>> operation_function;

  void addDigit(QString &number, const QString &input);
public:
  explicit Calculate(QObject *parent = nullptr);

  void addButton(QGridLayout *p_layout);

signals:
  void setNumber(const QString &);
public slots:
  void buttonClick();
};

#endif // CALCULATE_H
