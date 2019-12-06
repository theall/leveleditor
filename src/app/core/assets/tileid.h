#ifndef TTILEID_H
#define TTILEID_H

#include <QList>

#include "pixmapid.h"

class TTileId : public TPixmapId
{
public:
    TTileId(int id, TPixmap *pixmap);
    ~TTileId();

    int tilesetId() const;
    void setTilesetId(int tilesetId);

private:
    int mTilesetId;
};
typedef QList<TTileId*> TTileIdList;

#endif // TTILEID_H
