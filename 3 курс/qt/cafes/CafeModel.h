#ifndef CAFEMODEL_H
#define CAFEMODEL_H

#include <QAbstractTableModel>
#include <QVector>

struct Cafe {
    QString name;
    QString address;
    QString cuisine;
    QString hours;
};

class CafeModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit CafeModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addCafe(const Cafe &cafe);
    void removeCafe(int row);

private:
    QVector<Cafe> cafes;
};

#endif // CAFEMODEL_H
