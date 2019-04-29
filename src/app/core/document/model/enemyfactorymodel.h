#ifndef TENEMYFACTORYMODEL_H
#define TENEMYFACTORYMODEL_H

#include "../base/io.h"
#include "entity/enemyfactory.h"

#include <QAbstractTableModel>

class TEnemiyFactoryModel : public QAbstractTableModel, TIO
{
    Q_OBJECT

public:
    explicit TEnemiyFactoryModel(QObject *parent = Q_NULLPTR);
    ~TEnemiyFactoryModel();

    void clear();

    TEnemyFactoryList enemyFactoryList() const;
    void setEnemyFactoryList(const TEnemyFactoryList &enemyFactoryList);

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
    TEnemyFactoryList mEnemyFactoryList;
};
#endif // TENEMYFACTORYMODEL_H
