#ifndef TAREASMODEL_H
#define TAREASMODEL_H

#include "basemodel.h"
#include "entity/area.h"
#include "objectgeneric.hpp"
#include "genericmodel.h"

class TAreaModel : public TGenericModel<TArea>
{
    Q_OBJECT

public:
    explicit TAreaModel(QObject *parent = Q_NULLPTR);
    ~TAreaModel();

    void clear();

    TAreaList areaList() const;
    TArea *createArea(const QRect &rect);
    TArea *createArea(const QRectF &rect);

    void setPlatNameList(const QStringList &platNames);

signals:
    void objectInserted(const TAreaList &objectList, const QList<int> &indexList);
    void objectRemoved(const TAreaList &objectList, const QList<int> &indexList);

public:
    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    // TIO interface
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectMove(const TObjectList &objectList, const QList<int> &posList) Q_DECL_OVERRIDE;
};

#endif // TAREASMODEL_H
