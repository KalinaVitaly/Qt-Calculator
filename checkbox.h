#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QWidget>
#include <QCheckBox>

class Checkbox : public QWidget
{
    Q_OBJECT

private:
    QWidget *window;

public:
    explicit Checkbox(QWidget *parent = 0);

private slots:
    void showTitle(int);

signals:
    void checkBoxChange(int flag);
};

#endif // CHECKBOX_H
