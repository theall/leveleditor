#ifndef TDAREASMODEL_H
#define TDAREASMODEL_H

#include "basemodel.h"
#include "entity/darea.h"
#include "objectgeneric.hpp"

class TDAreaModel : public TBaseModel
{
    Q_OBJECT

public:
    TDAreaModel(QObject *parent = Q_NULLPTR);
    ~TDAreaModel();

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

public:
    DECL_GENERIC_FUNCTIONS(DArea);

signals:
    DECL_GENERIC_SIGNALS(DArea);
};

#endif // TDAREASMODEL_H
