#ifndef TITEMMODEL_H
#define TITEMMODEL_H

#include <QAbstractListModel>
#include "../assets/itemid.h"

class TItemModel : public QAbstractListModel
{
public:
    explicit TItemModel(QObject *parent = Q_NULLPTR);
    ~TItemModel();

    TItemIdList itemIdList() const;
    void setItemList(const TItemIdList &itemIdList);

private:
    TItemIdList mItemIdList;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // TITEMMODEL_H
