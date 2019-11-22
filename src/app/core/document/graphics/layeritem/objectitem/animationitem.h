#ifndef TANIMATIONITEM_H
#define TANIMATIONITEM_H

#include "tileitem.h"
#include "../../../model/entity/tile.h"
#include "../../../model/entity/animation.h"

class TAnimationItem : public TTileItem
{
public:
    TAnimationItem(TAnimation *animation, QGraphicsItem *parent);

    // TObjectItem interface
    void step() Q_DECL_OVERRIDE;
    TTile *getFirstTile() const;

private:
    TAnimation *mAnimation;
    int mCurrentIndex;
    TTile *mFirstTile;
    TTile *mCurrentTile;

    TFrame *getCurrentFrame() const;
    TFrame *getKeyFrameFromIndex(int index) const;
    int getKeyFrameIndexFromIndex(int index) const;
    void setCurrentTile(TTile *tile);

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};
typedef QList<TAnimationItem*> TAnimationItemList;

#endif // TANIMATIONITEM_H
