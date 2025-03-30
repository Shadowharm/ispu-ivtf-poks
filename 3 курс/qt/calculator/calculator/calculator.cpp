#include "calculator.h"
#include "QMessageBox"


Calculator::Calculator(QWidget *parent) : QWidget(parent), storedValue(0), operatorPressed(false) {
    createLayout();
}

Calculator::~Calculator() {
    delete display;
}

void Calculator::createLayout() {
    QGridLayout *layout = new QGridLayout(this);
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setStyleSheet("font-size: 24px; padding: 10px;");
    display->setAlignment(Qt::AlignRight);
    layout->addWidget(display, 0, 0, 1, 4);

    QSize buttonSize(70, 70);

    QString digits[10] = { "7", "8", "9", "4", "5", "6", "1", "2", "3", "0" };
    int positions[10][2] = { {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}, {3, 0}, {3, 1}, {3, 2}, {4, 1} };

    for (int i = 0; i < 10; ++i) {
        QPushButton *btn = new QPushButton(digits[i], this);
        btn->setFixedSize(buttonSize);
        btn->setStyleSheet("font-size: 24px;");
        connect(btn, &QPushButton::clicked, this, &Calculator::onDigitClicked);
        layout->addWidget(btn, positions[i][0], positions[i][1]);
    }

    QString operators[4] = { "+", "-", "*", "/" };
    for (int i = 0; i < 4; ++i) {
        QPushButton *btn = new QPushButton(operators[i], this);
        btn->setFixedSize(buttonSize);
        btn->setStyleSheet("font-size: 24px; background-color: #f0a500; color: white;");
        connect(btn, &QPushButton::clicked, this, &Calculator::onOperatorClicked);
        layout->addWidget(btn, i + 1, 3);
    }

    QPushButton *btnClear = new QPushButton("C", this);
    QPushButton *btnEqual = new QPushButton("=", this);


    btnClear->setFixedSize(buttonSize);
    btnEqual->setFixedSize(buttonSize);

    btnClear->setStyleSheet("font-size: 24px; background-color: #d9534f; color: white;");
    btnEqual->setStyleSheet("font-size: 24px; background-color: #5cb85c; color: white;");

    connect(btnClear, &QPushButton::clicked, this, &Calculator::onClearClicked);
    connect(btnEqual, &QPushButton::clicked, this, &Calculator::onEqualClicked);

    layout->addWidget(btnClear, 4, 0);
    layout->addWidget(btnEqual, 4, 2);
}

void Calculator::onDigitClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    if (operatorPressed) {
        display->clear();
        operatorPressed = false;
    }

    display->setText(display->text() + btn->text());
}

void Calculator::onOperatorClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    storedValue = display->text().toDouble();
    currentOperator = btn->text();
    operatorPressed = true;
}

void Calculator::onClearClicked() {
    display->clear();
    storedValue = 0;
    currentOperator.clear();
}

void Calculator::onEqualClicked() {
    double currentValue = display->text().toDouble();
    double result = 0;

    if (currentOperator == "+") result = storedValue + currentValue;
    else if (currentOperator == "-") result = storedValue - currentValue;
    else if (currentOperator == "*") result = storedValue * currentValue;
    else if (currentOperator == "/") {
        if (currentValue != 0) result = storedValue / currentValue;
        else {
            QMessageBox::critical(this, "Внимание", "На 0 делить нельзя");
            return;
        }
    }

    display->setText(QString::number(result));
    operatorPressed = true;
}
