#ifndef TPLATFORMSMODEL_H
#define TPLATFORMSMODEL_H

#include "basemodel.h"
#include "entity/plat.h"
#include "objectgeneric.hpp"

class TPlatModel : public TBaseModel
{
    Q_OBJECT

public:
    TPlatModel(QObject *parent = Q_NULLPTR);

    void clear();
    TPlatList platList() const;

    TPlat *createPlat();
    QStringList getPlatNames() const;

signals:
    void platInserted(const TPlatList &platList, const QList<int> &indexList);
    void platRemoved(const TPlatList &platList, const QList<int> &indexList);

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
    TPlatList mPlatList;

public:
    DECL_GENERIC_FUNCTIONS(Plat);

signals:
    DECL_GENERIC_SIGNALS(Plat);
};

#endif // TPLATFORMSMODEL_H
