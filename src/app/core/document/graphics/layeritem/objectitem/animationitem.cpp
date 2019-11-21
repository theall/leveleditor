#include "animationitem.h"

TAnimationItem::TAnimationItem(TAnimation *animation, QGraphicsItem *parent) :
    TTileItem(animation->getTile(), parent)
  , mAnimation(animation)
  , mCurrentIndex(-1)
  , mFirstTile(nullptr)
  , mCurrentTile(nullptr)
{
    if(!animation)
        return;

    mFirstTile = animation->getTile();
    mCurrentTile = mFirstTile;
    mCurrentPos = mFirstTile->pos();
}

void TAnimationItem::step()
{
    if(!mAnimation)
        return;

    if(!mFirstTile)
        return;

    QPointF speed = mFirstTile->getSpeed();
    QPointF position = mCurrentPos;
    if(speed.x() > 0.01 || speed.y() > 0.01) {
        position += speed;
        mCurrentPos = position;
    }

    mCurrentIndex++;
    int totalDuration = mAnimation->getTotalDuration();
    if(mCurrentIndex > totalDuration)
        mCurrentIndex = 0;
    TFrame *frame = getCurrentFrame();
    if(!frame)
        return;

    setCurrentTile(frame->getTile());
}

TTile *TAnimationItem::getFirstTile() const
{
    return mFirstTile;
}

TFrame *TAnimationItem::getCurrentFrame() const
{
    return getKeyFrameFromIndex(getKeyFrameIndexFromIndex(mCurrentIndex));
}

TFrame *TAnimationItem::getKeyFrameFromIndex(int index) const
{
    QList<TFrame*>  mFrameList = mAnimation->getFrameList();
    if(index<0 || index>=mFrameList.length())
        return nullptr;

    return mFrameList.at(index);
}

int TAnimationItem::getKeyFrameIndexFromIndex(int index) const
{
    TFrameList frameList = mAnimation->getFrameList();
    int i = -1;
    for(TFrame *frame : frameList) {
        i++;
        int duration = frame->getDuration();
        if(index < duration)
            return i;
        index -= duration;
    }
    return -1;
}

void TAnimationItem::setCurrentTile(TTile *tile)
{
    if(mCurrentTile == tile)
        return;

    mCurrentTile = tile;
}

void TAnimationItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(!mCurrentTile)
        return;

    painter->drawPixmap(mCurrentPos, mCurrentTile->pixmap());
}
