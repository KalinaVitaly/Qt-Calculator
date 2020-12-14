#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "ButtonsWidget.h"
#include <QLabel>
#include <QVBoxLayout>

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *vl;
    ButtonsWidget *buttons;
    QLabel *result_output;
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void setExpression(const QString &text);
};

#endif // MAINWINDOW_H
