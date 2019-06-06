#ifndef TAREASMODEL_H
#define TAREASMODEL_H

#include "basemodel.h"
#include "entity/area.h"
#include "objectgeneric.hpp"

class TAreaModel : public TBaseModel
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

public:
    DECL_GENERIC_FUNCTIONS(Area);

signals:
    DECL_GENERIC_SIGNALS(Area);
};

#endif // TAREASMODEL_H
