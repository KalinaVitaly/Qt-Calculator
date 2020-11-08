#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QCursor>
#include <calculate.h>
//QListWidget для списка из QString
#include <QCursor>
#include "checkbox.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
//  QWidget *w = new QWidget();
  QFrame *w = new QFrame();
  QGridLayout *layout = new QGridLayout();
  QLabel *label = new QLabel;
  Calculate *calc = new Calculate(label);
  QCursor cursor(Qt::PointingHandCursor);
  QPalette pallete;
  QColor color;
  Checkbox *cb = new Checkbox(w);
  layout->addWidget(cb,  1, 4, 1, 2);


  //label->setFrameStyle(QFrame::Plain | QFrame::HLine);
  //w->setFrameStyle(QFrame::Plain | QFrame::HLine);
  //w->setLineWidth(2);
  layout->addWidget(label, 0, 0, 1, 4);
  calc->addButton(layout);
  label->setText("0");
  label->setAlignment(Qt::AlignRight);
  w->setCursor(cursor);
  color.setRgb(0, 0, 0);
  pallete.setColor(QPalette::Window, color);
  color.setRgb(254, 254, 254);
  pallete.setColor(QPalette::WindowText, color);
  w->setPalette(pallete);
  w->setAutoFillBackground(true);

  QObject::connect(calc, SIGNAL(setNumber(const QString &)),
                   label, SLOT(setText(const QString &)));
  QObject::connect(cb, SIGNAL(checkBoxChange(int)),
                   calc, SLOT(changeTheme(int)));

  w->setLayout(layout);
  w->show();
  return a.exec();
}
