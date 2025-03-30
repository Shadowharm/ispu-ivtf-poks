/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_12;
    QPushButton *pushButton_9;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_2;
    QPushButton *pushButton_10;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_11;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(505, 625);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 150, 501, 421));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(9);
        gridLayout->setVerticalSpacing(4);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_12 = new QPushButton(gridLayoutWidget);
        pushButton_12->setObjectName("pushButton_12");

        gridLayout->addWidget(pushButton_12, 3, 3, 1, 1);

        pushButton_9 = new QPushButton(gridLayoutWidget);
        pushButton_9->setObjectName("pushButton_9");

        gridLayout->addWidget(pushButton_9, 3, 2, 1, 1);

        pushButton_7 = new QPushButton(gridLayoutWidget);
        pushButton_7->setObjectName("pushButton_7");

        gridLayout->addWidget(pushButton_7, 3, 0, 1, 1);

        pushButton_8 = new QPushButton(gridLayoutWidget);
        pushButton_8->setObjectName("pushButton_8");

        gridLayout->addWidget(pushButton_8, 3, 1, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout->addWidget(pushButton_2, 1, 1, 1, 1);

        pushButton_10 = new QPushButton(gridLayoutWidget);
        pushButton_10->setObjectName("pushButton_10");

        gridLayout->addWidget(pushButton_10, 1, 3, 1, 1);

        pushButton_5 = new QPushButton(gridLayoutWidget);
        pushButton_5->setObjectName("pushButton_5");

        gridLayout->addWidget(pushButton_5, 2, 0, 1, 1);

        pushButton_6 = new QPushButton(gridLayoutWidget);
        pushButton_6->setObjectName("pushButton_6");

        gridLayout->addWidget(pushButton_6, 2, 2, 1, 1);

        pushButton_11 = new QPushButton(gridLayoutWidget);
        pushButton_11->setObjectName("pushButton_11");

        gridLayout->addWidget(pushButton_11, 2, 3, 1, 1);

        pushButton_4 = new QPushButton(gridLayoutWidget);
        pushButton_4->setObjectName("pushButton_4");

        gridLayout->addWidget(pushButton_4, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(gridLayoutWidget);
        pushButton_3->setObjectName("pushButton_3");

        gridLayout->addWidget(pushButton_3, 1, 2, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        pushButton_13 = new QPushButton(gridLayoutWidget);
        pushButton_13->setObjectName("pushButton_13");

        gridLayout->addWidget(pushButton_13, 0, 1, 1, 1);

        pushButton_14 = new QPushButton(gridLayoutWidget);
        pushButton_14->setObjectName("pushButton_14");

        gridLayout->addWidget(pushButton_14, 0, 0, 1, 1);

        pushButton_15 = new QPushButton(gridLayoutWidget);
        pushButton_15->setObjectName("pushButton_15");
        pushButton_15->setIconSize(QSize(16, 16));

        gridLayout->addWidget(pushButton_15, 0, 2, 1, 1);

        pushButton_16 = new QPushButton(gridLayoutWidget);
        pushButton_16->setObjectName("pushButton_16");

        gridLayout->addWidget(pushButton_16, 0, 3, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 505, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
