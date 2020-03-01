#ifndef TWALLSMODEL_H
#define TWALLSMODEL_H

#include "basemodel.h"
#include "entity/wall.h"
#include "objectgeneric.hpp"
#include "genericmodel.h"

class TWallModel : public TGenericModel<TWall>
{
    Q_OBJECT

public:
    TWallModel(QObject *parent = Q_NULLPTR);

    void clear();
    TWallList wallList() const;

signals:
    void objectInserted(const TWallList &objectList, const QList<int> &indexList);
    void objectRemoved(const TWallList &objectList, const QList<int> &indexList);

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
    virtual void onObjectMove(const TObjectList &objectList, const QList<int> &posList) Q_DECL_OVERRIDE;
};

#endif // TWALLSMODEL_H
