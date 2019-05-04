#ifndef TDAREASMODEL_H
#define TDAREASMODEL_H

#include "basemodel.h"
#include "entity/darea.h"

class TDAreasModel : public TBaseModel
{
    Q_OBJECT

public:
    TDAreasModel(QObject *parent = Q_NULLPTR);
    ~TDAreasModel();

    TDAreaList dAreaList() const;
    void setDAreaList(const TDAreaList &dAreaList);

    void clear();

    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

private:
    TDAreaList mDAreaList;
};

#endif // TDAREASMODEL_H
