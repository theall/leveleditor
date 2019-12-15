#include "triggerid.h"

TTriggerId::TTriggerId(int id, TPixmap *on, TPixmap *off) :
    TPixmapId(id, nullptr)
  , mOnPixmap(on)
  , mOffPixmap(off)
{

}

TPixmap *TTriggerId::onPixmap() const
{
    return mOnPixmap;
}

void TTriggerId::setOnPixmap(TPixmap *onPixmap)
{
    mOnPixmap = onPixmap;
}

TPixmap *TTriggerId::offPixmap() const
{
    return mOffPixmap;
}

void TTriggerId::setOffPixmap(TPixmap *offPixmap)
{
    mOffPixmap = offPixmap;
}
