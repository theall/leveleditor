#ifndef TWALLSMODEL_H
#define TWALLSMODEL_H

#include "basemodel.h"
#include "entity/wall.h"

class TWallsModel : public TBaseModel
{
    Q_OBJECT

public:
    TWallsModel(QObject *parent = Q_NULLPTR);

    void clear();
    TWallList wallList() const;

    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

private:
    TWallList mWallList;
};

#endif // TWALLSMODEL_H
