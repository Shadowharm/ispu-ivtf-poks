#include "mainwindow.h"
#include <QInputDialog>

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    model = new CafeModel(this);
    tableView = new QTableView(this);
    tableView->setModel(model);


    this->resize(800, 600);

    CafeDelegate *delegate = new CafeDelegate(this);
    tableView->setItemDelegate(delegate);

    QPushButton *addButton = new QPushButton("Добавить кафе", this);
    QPushButton *removeButton = new QPushButton("Удалить кафе", this);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addCafe);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeSelectedCafe);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tableView);
    layout->addWidget(addButton);
    layout->addWidget(removeButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Кафе города");
}
void MainWindow::addCafe() {
    QString name = QInputDialog::getText(this, "Новое кафе", "Название:");
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название кафе не может быть пустым!");
        return;
    }
    QString address = QInputDialog::getText(this, "Новое кафе", "Адрес:");
    if (address.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Адрес кафе не может быть пустым!");
        return;
    }
    QStringList cuisines = {"Итальянская", "Французская", "Японская", "Русская", "Американская", "Китайская"};

    QString cuisine = QInputDialog::getItem(this, "Выбор типа кухни", "Тип кухни:", cuisines, 0, false);
    if (cuisine.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Выберите тип кухни!");
        return;
    }
    QString time = QInputDialog::getText(this, "Новое кафе", "Время работы");
    if (time.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Время работы не может быть пустым!");
        return;
    }
    if (!name.isEmpty()) {
        model->addCafe({name, address, cuisine, time});
    }
}

void MainWindow::removeSelectedCafe() {
    QModelIndex index = tableView->currentIndex();
    model->removeCafe(index.row());
}
