#ifndef TBOXESMODEL_H
#define TBOXESMODEL_H

#include "basemodel.h"
#include "entity/box.h"

class TBoxesModel : public TBaseModel
{
    Q_OBJECT

public:
    TBoxesModel(QObject *parent = nullptr);

    void clear();

    TBoxList boxList() const;

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
    TBoxList mBoxList;

};

#endif // TBOXESMODEL_H
