#ifndef LAYERSMODEL_H
#define LAYERSMODEL_H

#include "entity/layer.h"
#include "../base/io.h"
#include "../property/propertyobject.h"

#include <QAbstractTableModel>

class TLayersModel : public QAbstractTableModel, TIO
{
    Q_OBJECT

public:
    TLayersModel(QObject *parent = nullptr);
    ~TLayersModel();

    TLayerList getBackgroundLayerList() const;
    TLayerList getForegroundLayerList() const;

private:
    TLayerList mUnityLayerList;
    TLayerList mBackgroundLayerList;
    TLayerList mForegroundLayerList;

    // IO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
};

#endif // LAYERSMODEL_H
