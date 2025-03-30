#include "calculator.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Calculator calculator;
    calculator.setWindowTitle("Калькулятор");
    calculator.resize(300, 400);
    calculator.show();
    return app.exec();
}
