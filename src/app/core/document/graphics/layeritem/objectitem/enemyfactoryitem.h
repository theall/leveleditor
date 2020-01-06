#ifndef TENEMYFACTORYITEM_H
#define TENEMYFACTORYITEM_H

#include "objectitem.h"
#include "enemyitem.h"

class TEnemyModel;
class TEnemyFactoryItem : public TObjectItem
{
    Q_OBJECT

public:
    explicit TEnemyFactoryItem(TEnemyModel *enemyModel, QGraphicsItem *parent = Q_NULLPTR);
    ~TEnemyFactoryItem();

private slots:
    void slotEnemyInserted(const TEnemyList &enemyList, const QList<int> &);
    void slotEnemyRemoved(const TEnemyList &enemyList, const QList<int> &);

private:
    TEnemyItemList mEnemyItemList;
    void addEnemy(TEnemy *enemy);
    void calcBoundingRect();

private slots:
    void slotBoundingRectChanged(const QRectF &boundingRect);

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
typedef QList<TEnemyFactoryItem*> TEnemyFactoryItemList;

#endif // TENEMYFACTORYITEM_H
