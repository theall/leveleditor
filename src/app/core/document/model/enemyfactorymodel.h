#ifndef TENEMYFACTORYMODEL_H
#define TENEMYFACTORYMODEL_H

#include "basemodel.h"
#include "entity/enemyfactory.h"
#include "objectgeneric.hpp"
#include "genericmodel.h"
#include "enemymodel.h"

#define TILE_DEFAULT_POS_X 5000
#define TILE_DEFAULT_POS_Y 5000

class TEnemyModel;
typedef QList<TEnemyModel*> TEnemyModelList;

class TEnemyFactoryModel : public TGenericModel<TEnemyFactory>
{
    Q_OBJECT

public:
    explicit TEnemyFactoryModel(QObject *parent = Q_NULLPTR);
    ~TEnemyFactoryModel();

    void clear();

    TEnemyFactoryList enemyFactoryList() const;
    TEnemyFactory *getEnemyFactory(int index);
    void setEnemyFactoryList(const TEnemyFactoryList &enemyFactoryList);

    TEnemyModelList enemyModelList() const;
    TEnemyModel *getEnemyModel(int index);
    void setEnemyModelList(const TEnemyModelList &enemyModelList);
    void getFactoryIndex(int index);
    TEnemy *createEnemy(TFaceId *faceId, const QPointF &pos = QPointF(TILE_DEFAULT_POS_X,TILE_DEFAULT_POS_Y));
    TEnemyFactory *createEnemyFactory();
    TEnemyModel *getCurrentEnemyModel();

    int getCurrentIndex() const;
    void setCurrentIndex(int currentIndex);

private:
    int mCurrentIndex;
    TEnemyModelList mEnemyModelList;

signals:
    void objectInserted(const TEnemyFactoryList &objectList, const QList<int> &indexList);
    void objectRemoved(const TEnemyFactoryList &objectList, const QList<int> &indexList);

    // TIO interface
public:
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

protected:
    virtual void onObjectInserted(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;
    virtual void onObjectRemoved(const TObjectList &objectList, const QList<int> &indexList) Q_DECL_OVERRIDE;

};
#endif // TENEMYFACTORYMODEL_H
