#include "alarm.h"

AlarmClock::AlarmClock() : QWidget() {
    lcdTime = new QLCDNumber(this);
    lcdTime->setDigitCount(5);
    lcdTime->setSegmentStyle(QLCDNumber::Flat);

    QLabel *labelHours = new QLabel("Часы:", this);
    QLabel *labelMinutes = new QLabel("Минуты:", this);

    hourSpin = new QSpinBox(this);
    hourSpin->setRange(0, 23);

    minuteSpin = new QSpinBox(this);
    minuteSpin->setRange(0, 59);

    enableAlarm = new QCheckBox("Включить будильник", this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AlarmClock::updateCurrentTime);
    connect(timer, &QTimer::timeout, this, &AlarmClock::checkAlarm);
    timer->start(1000);

    // Компоновка элементов
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(lcdTime);

    QHBoxLayout *timeLayout = new QHBoxLayout();
    timeLayout->addWidget(labelHours);
    timeLayout->addWidget(hourSpin);
    timeLayout->addWidget(labelMinutes);]
    timeLayout->addWidget(minuteSpin);
    mainLayout->addLayout(timeLayout);

    mainLayout->addWidget(enableAlarm);

    setLayout(mainLayout);
    setWindowTitle("Будильник");
}

AlarmClock::~AlarmClock() {}

void AlarmClock::updateCurrentTime() {
    lcdTime->display(QTime::currentTime().toString("HH:mm"));
}

void AlarmClock::checkAlarm() {
    if (enableAlarm->isChecked()) {
        QTime currentTime = QTime::currentTime();
        if (currentTime.hour() == hourSpin->value() && currentTime.minute() == minuteSpin->value()) {
            QMessageBox::information(this, "Будильник", "Пора вставать!");
            enableAlarm->setChecked(false);
        }
    }
}
