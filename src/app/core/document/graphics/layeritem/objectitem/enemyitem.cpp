#include "enemyitem.h"

TEnemyItem::TEnemyItem(TEnemy *enemy, QGraphicsItem *parent) :
    TObjectItem(enemy, parent)
  , mEnemy(enemy)
{
    Q_ASSERT(mEnemy);
    setBorderColor(Qt::yellow);
}

TEnemyItem::~TEnemyItem()
{

}

TEnemy *TEnemyItem::enemy() const
{
    return mEnemy;
}

void TEnemyItem::propertyValueChanged(PropertyID)
{

}
