#ifndef TRESPAWNSMODEL_H
#define TRESPAWNSMODEL_H

#include "basemodel.h"
#include "entity/respawn.h"
#include "objectgeneric.hpp"
#include "genericmodel.h"

#include <QList>
#include <QPoint>

class TRespawnModel : public TGenericModel<TRespawn>
{
    Q_OBJECT

public:
    TRespawnModel(QObject *parent = Q_NULLPTR);

    void clear();
    TPointObject *getTPointObject(int index);
    TRespawnList respawnList() const;
    int indexOf(TRespawn *respawn) const;
    int pointObjectIndex(TPointObject *pointObject);

signals:
    void objectInserted(const TRespawnList &objectList, const QList<int> &indexList);
    void objectRemoved(const TRespawnList &objectList, const QList<int> &indexList);
    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
//    QModelIndex index(int row, int column, const QModelIndex &parent) const;
//    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectMove(const TObjectList &objectList, const QList<int> &posList) Q_DECL_OVERRIDE;
};

#endif // TRESPAWNSMODEL_H
