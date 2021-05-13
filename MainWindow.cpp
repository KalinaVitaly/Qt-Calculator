#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    vl = new QVBoxLayout(this);
    buttons = new ButtonsWidget;
    result_output = new QLabel("0");

    result_output->setStyleSheet("qproperty-alignment: 'AlignVCenter | AlignRight';"\
                                 "border : 1px solid gray;"\
                                 "font-size : 20px;");

    connect(buttons, &ButtonsWidget::setNumber,
            this, &MainWindow::setExpression);

    vl->addWidget(result_output, 0);
    vl->addWidget(buttons, 0);
    this->setFixedSize(380, 440);
}

void MainWindow::setExpression(const QString &text) {
    qDebug("Set expression");
    result_output->setText(text);
}
