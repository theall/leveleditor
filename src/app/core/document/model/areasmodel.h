#ifndef TAREASMODEL_H
#define TAREASMODEL_H

#include "basemodel.h"
#include "entity/area.h"

class TAreasModel : public TBaseModel
{
    Q_OBJECT

public:
    explicit TAreasModel(QObject *parent = Q_NULLPTR);
    ~TAreasModel();

    void clear();

    TAreaList areaList() const;
    TArea *createArea(const QRect &rect);
    TArea *createArea(const QRectF &rect);

    void insertArea(TArea *area, int index = -1);
    void insertArea(const TAreaList &areaList, const QList<int> &indexList = QList<int>());
    int removeArea(int index);
    int removeArea(TArea *area);
    QList<int> removeArea(const QList<int> &indexList);
    QList<int> removeArea(const TAreaList &areaList);

signals:
    void areaInserted(const TAreaList &areaList, const QList<int> &indexList);
    void areaRemoved(const TAreaList &areaList, const QList<int> &indexList);

private:
    TAreaList mAreaList;

public:
    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    // TIO interface
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // TBaseModel interface
public:
    void insertObjects(const TObjectList &objectList, const QList<int> &indexList);
    QList<int> removeObjects(const TObjectList &objectList);
};

#endif // TAREASMODEL_H
