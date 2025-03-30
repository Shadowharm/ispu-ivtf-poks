#ifndef ALARMCLOCK_H
#define ALARMCLOCK_H

#include <QWidget>
#include <QLCDNumber>
#include <QSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <QTime>

class AlarmClock : public QWidget {
    Q_OBJECT

public:
    explicit AlarmClock();
    ~AlarmClock();

private slots:
    void updateCurrentTime();
    void checkAlarm();

private:
    QLCDNumber *lcdTime;
    QSpinBox *hourSpin;
    QSpinBox *minuteSpin;
    QCheckBox *enableAlarm;
    QTimer *timer;
};

#endif // ALARMCLOCK_H
