#include "CafeModel.h"

CafeModel::CafeModel(QObject *parent) : QAbstractTableModel(parent) {}

int CafeModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : cafes.size();
}

int CafeModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 4;
}

QVariant CafeModel::data(const QModelIndex &index, int role) const {
    if (index.row() >= cafes.size())
        return QVariant();

    const Cafe &cafe = cafes[index.row()];
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0: return cafe.name;
        case 1: return cafe.address;
        case 2: return cafe.cuisine;
        case 3: return cafe.hours;
        }
    }
    return QVariant();
}

QVariant CafeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return "Название";
            case 1: return "Адрес";
            case 2: return "Тип кухни";
            case 3: return "Время работы";
            }
        }
    }
    return QVariant();
}

bool CafeModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::EditRole) {
        if (index.row() < 0 || index.row() >= cafes.size())
            return false;

        Cafe &cafe = cafes[index.row()];
        switch (index.column()) {
        case 0: cafe.name = value.toString(); break;
        case 1: cafe.address = value.toString(); break;
        case 2: cafe.cuisine = value.toString(); break;
        case 3: cafe.hours = value.toString(); break;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags CafeModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

void CafeModel::addCafe(const Cafe &cafe) {
    beginInsertRows(QModelIndex(), cafes.size(), cafes.size());
    cafes.append(cafe);
    endInsertRows();
}

void CafeModel::removeCafe(int row) {
    if (row < 0 || row >= cafes.size()) return;
    beginRemoveRows(QModelIndex(), row, row);
    cafes.removeAt(row);
    endRemoveRows();
}
