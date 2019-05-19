#ifndef TTILESET_H
#define TTILESET_H

#include "tileid.h"

class TTileset
{
public:
    TTileset();
    TTileset(int id);
    ~TTileset();

    int id() const;
    void setId(int id);

    TTileIdList tileList() const;
    void setTileList(const TTileIdList &tileList);

    void add(TTileId *tile);
    void sort();

    TTileId *getTileId(int index) const;
    int indexOf(TTileId *tileId) const;

private:
    int mId;
    TTileIdList mTileList;
};

typedef QList<TTileset*> TilesetList;
#endif // TTILESET_H
