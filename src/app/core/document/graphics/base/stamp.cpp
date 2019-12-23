#include "stamp.h"

#include "../../../assets/tileid.h"

TStamp::TStamp()
{

}

TPixmapId *TStamp::pixmapId() const
{
    return mPixmapId;
}

TTileId *TStamp::getTileId() const
{
    return (TTileId*)mPixmapId;
}

void TStamp::setPixmapId(TPixmapId *pixmapId)
{
    mPixmapId = pixmapId;
}

QPixmap TStamp::pixmap() const
{
    if(mPixmapId == nullptr)
        return QPixmap();

    return mPixmapId->primitive();
}
