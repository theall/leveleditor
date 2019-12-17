#ifndef TPLATFORMSMODEL_H
#define TPLATFORMSMODEL_H

#include "basemodel.h"
#include "entity/plat.h"
#include "objectgeneric.hpp"
#include "genericmodel.h"

class TPlatModel : public TGenericModel<TPlat>
{
    Q_OBJECT

public:
    TPlatModel(QObject *parent = Q_NULLPTR);

    void clear();
    TPlatList platList() const;

    TPlat *createPlat();
    QStringList getPlatNames() const;

signals:
    void platInserted(const TPlatList &platList, const QList<int> &indexList);
    void platRemoved(const TPlatList &platList, const QList<int> &indexList);
    void objectInserted(const TPlatList &objectList, const QList<int> &indexList);
    void objectRemoved(const TPlatList &objectList, const QList<int> &indexList);

    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
};

#endif // TPLATFORMSMODEL_H
