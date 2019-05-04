#ifndef TPLATFORMSMODEL_H
#define TPLATFORMSMODEL_H

#include "basemodel.h"
#include "entity/plat.h"

class TPlatformsModel : public TBaseModel
{
    Q_OBJECT

public:
    TPlatformsModel(QObject *parent = Q_NULLPTR);

    void clear();
    TPlatList platList() const;

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
    TPlatList mPlatList;
};

#endif // TPLATFORMSMODEL_H
