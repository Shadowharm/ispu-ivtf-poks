#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include "CafeModel.h"
#include "CafeDelegate.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void addCafe();
    void removeSelectedCafe();

private:
    CafeModel *model;
    QTableView *tableView;
};

#endif // MAINWINDOW_H
