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

    void clear();

    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    QList<TLayer *> layerList() const;
    int addLayer(const QString &name);
    int addLayer(TLayer *layer, int index=-1);
    int removeLayer(TLayer *layer);
    int removeLayer(int index);
    QList<int> removeLayers(const QList<TLayer *> &layers);
    QList<int> removeLayers(const QList<int> &layerList);

    TLayer *getLayer(int index);
    int count();

private slots:
    void slotLayerNameChanged(const QString &newName);

private:
    TLayer *mCurrentLayer;
    QList<TLayer*> mLayerList;

    TLayer *getLayer(const QModelIndex &index);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;
};

#endif // LAYERSMODEL_H
