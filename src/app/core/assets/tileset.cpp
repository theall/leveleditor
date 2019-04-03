#include "tileset.h"

bool idCompare(TTileId *id1, TTileId *id2)
{
    return id1->id() < id2->id();
}

TTileset::TTileset()
{

}

TTileset::TTileset(int id) :
    mId(id)
{

}

TTileset::~TTileset()
{
    for(auto x : mTileList) {
        delete x;
    }
    mTileList.clear();
}

int TTileset::id() const
{
    return mId;
}

void TTileset::setId(int id)
{
    mId = id;
}

TTileIdList TTileset::tileList() const
{
    return mTileList;
}

void TTileset::setTileList(const TTileIdList &tileList)
{
    mTileList = tileList;
}

void TTileset::add(TTileId *tile)
{
    mTileList.append(tile);
}

void TTileset::sort()
{
    qSort(mTileList.begin(), mTileList.end(), idCompare);
}
