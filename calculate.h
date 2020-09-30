#ifndef CALCULATE_H
#define CALCULATE_H

#include <QObject>
#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QMap>

class Calculate : public QObject
{
  Q_OBJECT
private:
  double first_number;
  double second_number;
  double result;
  bool is_operation_possible;
  QString operation;

  QMap<QString, std::function<double(double, double)>> operation_function;
public:
  explicit Calculate(QObject *parent = nullptr);

  void addButton(QGridLayout *p_layout);

signals:
  void setNumber(const QString &);
public slots:
  void buttonClick();
};

#endif // CALCULATE_H
