#include "tileid.h"

TTileId::TTileId(int id, TPixmap *pixmap) :
    TPixmapId(id, pixmap)
  , mTilesetId(-1)
{

}

TTileId::~TTileId()
{

}

int TTileId::tilesetId() const
{
    return mTilesetId;
}

void TTileId::setTilesetId(int tilesetId)
{
    mTilesetId = tilesetId;
}
