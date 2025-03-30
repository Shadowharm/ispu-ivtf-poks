#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onClearClicked();
    void onEqualClicked();

private:
    QLineEdit *display;
    QString currentOperator;
    double storedValue;
    bool operatorPressed;

    void createLayout();
};

#endif // CALCULATOR_H
