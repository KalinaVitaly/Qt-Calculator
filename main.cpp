#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <calculate.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QWidget *w = new QWidget();
  QGridLayout *layout = new QGridLayout();
  QLabel *label = new QLabel;
  Calculate *calc = new Calculate;

  layout->addWidget(label, 0, 0, 1, 4);
  calc->addButton(layout);
  label->setText("0");
  label->setAlignment(Qt::AlignRight);
  label->adjustSize();

  QString num("-1.0");

  qDebug() << QString::number(-1.0) << " " << num.toDouble();

  QObject::connect(calc, SIGNAL(setNumber(const QString &)),
                   label, SLOT(setText(const QString &)));

  w->setLayout(layout);
  w->show();
  return a.exec();
}
