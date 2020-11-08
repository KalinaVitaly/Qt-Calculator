#include "checkbox.h"
#include <QDebug>

Checkbox::Checkbox(QWidget *parent)
    :QWidget(parent),
      window(parent)
{
    QCheckBox *cb = new QCheckBox("&Color", this);
    cb->setCheckState(Qt::Checked);
    connect(cb, SIGNAL(stateChanged(int)), this, SLOT(showTitle(int)));
}

void Checkbox::showTitle(int state)
{
    if (state == Qt::Checked) {
        window->setWindowTitle("black theme");
        emit checkBoxChange(true);
    }
    else {
        window->setWindowTitle("white theme");
        emit checkBoxChange(false);
    }
}
