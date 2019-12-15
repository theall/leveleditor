#include "chunkid.h"

bool idCompare(TPixmapId *id1, TPixmapId *id2)
{
    return id1->id() < id2->id();
}

TChunkId::TChunkId(int id, TPixmap *pixmap) :
    TPixmapId(id, pixmap)
{

}

void TChunkId::add(int id, TPixmap *pixmap)
{
    add(new TPixmapId(id, pixmap));
}

void TChunkId::add(TPixmapId *pixmapId)
{
    mPixmapIdList.append(pixmapId);
}

void TChunkId::sort()
{
    qSort(mPixmapIdList.begin(), mPixmapIdList.end(), idCompare);
}
