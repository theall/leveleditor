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

    TEnemy *createEnemy(TFaceId *faceId, const QPointF &pos);
    TEnemy *createEnemy();

signals:
    void objectInserted(const TEnemyList &objectList, const QList<int> &indexList);
    void objectRemoved(const TEnemyList &objectList, const QList<int> &indexList);

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

    // TBaseModel interface
protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList);
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList);
};

#endif // TENEMYMODEL_H
