#ifndef TENEMYFACTORYMODEL_H
#define TENEMYFACTORYMODEL_H

#include "basemodel.h"
#include "entity/enemyfactory.h"
#include "objectgeneric.hpp"
#include "genericmodel.h"

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
    void setEnemyFactoryList(const TEnemyFactoryList &enemyFactoryList);

    TEnemyModelList enemyModelList() const;
    void setEnemyModelList(const TEnemyModelList &enemyModelList);

    TEnemyFactory *createEnemyFactory();

private:
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
