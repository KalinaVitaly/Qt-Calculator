#ifndef BUTTONSWIDGET_H
#define BUTTONSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class ButtonsWidget : public QWidget
{
    Q_OBJECT
private:
    QVector<QChar> panel_symbols;
    QVector<QPushButton *> buttons;
    QGridLayout *gl_buttons;
    QString current_expression;

    void setButtonsParams();
    void setButtonColor(QPushButton &button, QChar symbol, bool theme);
    void clickEqualButton(double &result);
    void clickPointButton();
    void clickDigitButton(const QString &input);
    void clickOperationButton(const QString &input);
    bool isOperation(const QChar &symbol) const;

public:
    ButtonsWidget(QWidget * parent = nullptr);

public slots:
    void buttonClick();

signals:
  void setNumber(const QString &);
};

#endif // BUTTONSWIDGET_H
