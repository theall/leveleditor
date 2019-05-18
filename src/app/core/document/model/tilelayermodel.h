#ifndef TTILELAYERMODEL_H
#define TTILELAYERMODEL_H

#include "basemodel.h"
#include "entity/layer.h"

class TTileLayerModel : public TBaseModel
{
    Q_OBJECT

public:
    TTileLayerModel(QObject *parent = nullptr);
    ~TTileLayerModel();

    TLayer *layer() const;

private:
    TLayer *mLayer;

    // IO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    // TBaseModel interface
public:
    void insertObjects(const TObjectList &objectList, const QList<int> &indexList);
    QList<int> removeObjects(const TObjectList &objectList);
};


#endif // TTILELAYERMODEL_H
