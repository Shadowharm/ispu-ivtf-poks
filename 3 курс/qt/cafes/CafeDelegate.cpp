#include "CafeDelegate.h"
#include <QComboBox>
#include <QPainter>
#include <QLineEdit>
#include <QMessageBox>


CafeDelegate::CafeDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *CafeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 2) {
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->addItems({"Итальянская", "Французская", "Японская", "Русская", "Американская", "Китайская"});
        return comboBox;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void CafeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    if (index.column() == 2) {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (comboBox) {
            comboBox->setCurrentText(index.data(Qt::EditRole).toString());
        }
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void CafeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QString newValue;

    if (index.column() == 2) {
        QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
        if (comboBox) {
            newValue = comboBox->currentText();
        }
    } else {
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(editor);
        if (lineEdit) {
            newValue = lineEdit->text().trimmed();
        }
    }

    if (newValue.isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", "Поле не может быть пустым!");
        return;
    }

    model->setData(index, newValue, Qt::EditRole);
}

void CafeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const {    
    if (index.column() == 2) {
        if (!(option.state & QStyle::State_Selected)) {
            painter->drawText(option.rect, Qt::AlignVCenter | Qt::AlignLeft,
                              index.data(Qt::DisplayRole).toString());
        }
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
