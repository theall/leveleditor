#include "tileset.h"

bool idCompare(TTileId *id1, TTileId *id2)
{
    return id1->id() < id2->id();
}

TTileSet::TTileSet()
{

}

TTileSet::TTileSet(int id) :
    mId(id)
{

}

TTileSet::~TTileSet()
{
    for(auto x : mTileList) {
        delete x;
    }
    mTileList.clear();
}

int TTileSet::id() const
{
    return mId;
}

void TTileSet::setId(int id)
{
    mId = id;
}

TTileIdList TTileSet::tileList() const
{
    return mTileList;
}

void TTileSet::setTileList(const TTileIdList &tileList)
{
    mTileList = tileList;
}

void TTileSet::add(TTileId *tile)
{
    mTileList.append(tile);
}

void TTileSet::sort()
{
    qSort(mTileList.begin(), mTileList.end(), idCompare);
}
