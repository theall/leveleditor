#include "enemyitem.h"

#include <QPainter>

TEnemyItem::TEnemyItem(TEnemy *enemy, QGraphicsItem *parent) :
    TObjectItem(enemy, parent)
  , mEnemy(enemy)
{
    Q_ASSERT(mEnemy);

    mCurrentPos = mEnemy->pos();
    setBorderColor(Qt::yellow);
    setAnchor(TObjectItem::BOTTOM_CENTER);
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

void TEnemyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    TPixmap *pixmap = mEnemy->getPixmap();
    if(!pixmap)
        return;

    QPixmap p = pixmap->pixmap();
    QPointF currentPos = getCurrentPos();
    currentPos -= QPointF(p.width()/2, p.height());
    painter->drawPixmap(currentPos, p);
}
