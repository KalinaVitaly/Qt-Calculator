#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <calculate.h>

#include <QCursor>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QWidget *w = new QWidget();
  QGridLayout *layout = new QGridLayout();
  QLabel *label = new QLabel;
  Calculate *calc = new Calculate;
  QPalette pallete;
  QColor color;

  layout->addWidget(label, 0, 0, 1, 4);
  calc->addButton(layout);
  label->setText("0");
  label->setAlignment(Qt::AlignRight);

  color.setRgb(0, 0, 0);
  pallete.setColor(QPalette::Window, color);
  color.setRgb(254, 254, 254);
  pallete.setColor(QPalette::WindowText, color);
  w->setPalette(pallete);
  w->setAutoFillBackground(true);


  QObject::connect(calc, SIGNAL(setNumber(const QString &)),
                   label, SLOT(setText(const QString &)));

  w->setLayout(layout);
  w->show();
  return a.exec();
}
