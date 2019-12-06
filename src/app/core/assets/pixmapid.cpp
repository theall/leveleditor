#include "pixmapid.h"

TPixmapId::TPixmapId(int id, TPixmap *pixmap) :
    mId(id)
  , mPixmap(pixmap)
{

}

TPixmapId::~TPixmapId()
{
    if(mPixmap) {
        delete mPixmap;
        mPixmap = nullptr;
    }
}

int TPixmapId::id() const
{
    return mId;
}

void TPixmapId::setId(int id)
{
    mId = id;
}

TPixmap *TPixmapId::pixmap() const
{
    return mPixmap;
}

void TPixmapId::setPixmap(TPixmap *pixmap)
{
    mPixmap = pixmap;
}
