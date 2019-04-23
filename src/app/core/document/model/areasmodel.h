#ifndef TAREASMODEL_H
#define TAREASMODEL_H

#include "../base/io.h"
#include "entity/area.h"

#include <QAbstractTableModel>

class TAreasModel : public QAbstractTableModel, TIO
{
    Q_OBJECT

public:
    TAreasModel(QObject *parent = Q_NULLPTR);

    void clear();

    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    TAreaList areaList() const;

private:
    TAreaList mAreaList;
};

#endif // TAREASMODEL_H
