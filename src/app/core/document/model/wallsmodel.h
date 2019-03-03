#ifndef TWALLSMODEL_H
#define TWALLSMODEL_H

#include "../base/io.h"

#include <QAbstractTableModel>

class TWallsModel : public QAbstractTableModel, TIO
{
    Q_OBJECT

public:
    TWallsModel(QObject *parent = Q_NULLPTR);

    void clear();

    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
};

#endif // TWALLSMODEL_H
