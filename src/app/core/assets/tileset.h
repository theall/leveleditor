#ifndef TTILESET_H
#define TTILESET_H

#include "tileid.h"

class TTileSet
{
public:
    TTileSet();
    TTileSet(int id);
    ~TTileSet();

    int id() const;
    void setId(int id);

    TTileIdList tileList() const;
    void setTileList(const TTileIdList &tileList);

    void add(TTileId *tile);
    void sort();

private:
    int mId;
    TTileIdList mTileList;
};

typedef QList<TTileSet*> TileSetList;
#endif // TTILESET_H
