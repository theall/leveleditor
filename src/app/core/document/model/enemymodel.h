#ifndef TENEMYMODEL_H
#define TENEMYMODEL_H

#include "genericmodel.h"
#include "objectgeneric.hpp"
#include "entity/enemy.h"

#define TILE_DEFAULT_POS_X 5000
#define TILE_DEFAULT_POS_Y 5000

class TEnemyFactory;
class TEnemyModel : public TGenericModel<TEnemy>
{
    Q_OBJECT

public:
    TEnemyModel(QObject *parent = Q_NULLPTR);

    TEnemyFactory *enemyFactory() const;
    void setEnemyFactory(TEnemyFactory *enemyFactory);

    TEnemy *createEnemy(TFaceId *faceId, const QPointF &pos = QPointF(TILE_DEFAULT_POS_X,TILE_DEFAULT_POS_Y));
    TEnemy *createEnemy();

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
