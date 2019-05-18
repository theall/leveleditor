#ifndef TTILEID_H
#define TTILEID_H

#include <QList>

#include "pixmap.h"

class TTileId
{
public:
    TTileId();
    TTileId(int id, TPixmap *pixmap);
    ~TTileId();

    int id() const;
    void setId(int id);

    TPixmap *pixmap() const;
    void setPixmap(TPixmap *pixmap);

    int tilesetId() const;
    void setTilesetId(int tilesetId);

private:
    int mId;
    int mTilesetId;
    TPixmap *mPixmap;
};
typedef QList<TTileId*> TTileIdList;

#endif // TTILEID_H
