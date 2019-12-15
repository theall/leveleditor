#ifndef TSHOTMODEL_H
#define TSHOTMODEL_H

#include <QAbstractListModel>
#include "../assets/shotid.h"

class TShotModel :  public QAbstractListModel
{

public:
    explicit TShotModel(QObject *parent = Q_NULLPTR);
    ~TShotModel();

    TShotList shotIdList() const;
    void setShotIdList(const TShotList &shotIdList);

private:
    TShotList mShotList;

public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // TSHOTMODEL_H
