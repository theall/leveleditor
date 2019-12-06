#ifndef TCHUNKID_H
#define TCHUNKID_H

#include "pixmapid.h"

class TChunkId : public TPixmapId
{
public:
    TChunkId(int id, TPixmap *pixmap);
};
typedef QList<TChunkId*> TChunkList;

#endif // TCHUNKID_H
