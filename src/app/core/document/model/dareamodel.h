#ifndef TDAREASMODEL_H
#define TDAREASMODEL_H

#include "basemodel.h"
#include "entity/darea.h"
#include "objectgeneric.hpp"
#include "genericmodel.h"

class TDAreaModel : public TGenericModel<TDArea>
{
    Q_OBJECT

public:
    TDAreaModel(QObject *parent = Q_NULLPTR);
    ~TDAreaModel();

    TDAreaList dAreaList() const;
    void setDAreaList(const TDAreaList &dAreaList);

    void clear();

signals:
    void objectInserted(const TDAreaList &objectList, const QList<int> &indexList);
    void objectRemoved(const TDAreaList &objectList, const QList<int> &indexList);

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

#endif // TDAREASMODEL_H
