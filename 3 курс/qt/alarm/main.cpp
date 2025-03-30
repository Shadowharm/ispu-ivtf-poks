#include <QApplication>
#include "alarm.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    AlarmClock alarm;
    alarm.resize(300, 200);
    alarm.show();
    return app.exec();
}
