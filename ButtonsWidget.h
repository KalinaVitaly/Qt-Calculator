#ifndef BUTTONSWIDGET_H
#define BUTTONSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include "calculate.h"

class ButtonsWidget : public QWidget
{
    Q_OBJECT
private:
    QVector<QChar> panel_symbols;
    QVector<QPushButton *> buttons;
    QGridLayout *gl_buttons;
    QString current_expression;
    Calculate *calc;

    void setButtonsParams();
    void setButtonColor(QPushButton &button, QChar symbol);
    void clickEqualButton(double &result);
    void clickPointButton();
    void clickDigitButton(const QString &input);
    void clickOperationButton(const QString &input);
    bool isOperation(const QChar &symbol) const;
    bool correctBracketSequence(const QString &expression);

public:
    ButtonsWidget(QWidget * parent = nullptr);

public slots:
    void buttonClick();
    void setResult(const QString & result);

signals:
  void setNumber(const QString &);
  void clickedEquals(const QString &);
};

#endif // BUTTONSWIDGET_H
