#include "stamp.h"

#include "../../../assets/tileid.h"
#include "../../../assets/faceid.h"

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

TFaceId *TStamp::getFaceId() const
{
    return (TFaceId*)mPixmapId;
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
