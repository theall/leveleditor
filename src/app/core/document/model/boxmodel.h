#ifndef TBOXESMODEL_H
#define TBOXESMODEL_H

#include "basemodel.h"
#include "entity/box.h"
#include "objectgeneric.hpp"
#include "genericmodel.h"

class TBoxModel : public TGenericModel<TBox>
{
    Q_OBJECT

public:
    TBoxModel(QObject *parent = nullptr);

    void clear();

    TBoxList boxList() const;

    // TIO interface

signals:
    void objectInserted(const TBoxList &objectList, const QList<int> &indexList);
    void objectRemoved(const TBoxList &objectList, const QList<int> &indexList);

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

#endif // TBOXESMODEL_H
