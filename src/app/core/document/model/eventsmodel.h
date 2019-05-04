#ifndef TEVENTSMODEL_H
#define TEVENTSMODEL_H

#include "basemodel.h"

class TEventsModel : public TBaseModel
{
    Q_OBJECT

public:
    TEventsModel(QObject *parent = Q_NULLPTR);

    void clear();
    QList<int> eventList() const;

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
    QList<int> mEventList;
};

#endif // TEVENTSMODEL_H
