#ifndef TENEMYMODEL_H
#define TENEMYMODEL_H

#include "genericmodel.h"
#include "objectgeneric.hpp"
#include "entity/enemy.h"

class TEnemyFactory;
class TEnemyModel : public TGenericModel<TEnemy>
{
    Q_OBJECT

public:
    TEnemyModel(QObject *parent = Q_NULLPTR);

    TEnemyFactory *enemyFactory() const;
    void setEnemyFactory(TEnemyFactory *enemyFactory);

private:
    TEnemyFactory *mEnemyFactory;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const;
    void readFromStream(QDataStream &stream);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // TENEMYMODEL_H
