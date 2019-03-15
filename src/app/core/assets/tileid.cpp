#include "tileid.h"

TTileId::TTileId() :
    mId(-1)
  , mPixmap(nullptr)
{

}

TTileId::TTileId(int id, TPixmap *pixmap) :
    mId(id)
  , mPixmap(pixmap)
{

}

TTileId::~TTileId()
{
    if(mPixmap) {
        delete mPixmap;
        mPixmap = nullptr;
    }
}

int TTileId::id() const
{
    return mId;
}

void TTileId::setId(int id)
{
    mId = id;
}

TPixmap *TTileId::pixmap() const
{
    return mPixmap;
}

void TTileId::setPixmap(TPixmap *pixmap)
{
    mPixmap = pixmap;
}
