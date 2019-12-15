#ifndef TCHUNKID_H
#define TCHUNKID_H

#include "pixmapid.h"

class TChunkId : public TPixmapId
{
public:
    TChunkId(int id, TPixmap *pixmap);

    void add(int id, TPixmap *pixmap);
    void add(TPixmapId *pixmapId);
    void sort();

private:
    TPixmapIdList mPixmapIdList;
};
typedef QList<TChunkId*> TChunkList;

#endif // TCHUNKID_H
