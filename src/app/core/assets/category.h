#ifndef TCATEGORY_H
#define TCATEGORY_H

#include "pixmapid.h"

enum Category {
    PLAYER = 0,
    ITEM,
    SHOT,
    CHUNK
};

class TCategory
{
public:
    TCategory();

    TPixmapId *getPixmapId(Category set, int id);

private:
    TPixmapIdList mFaceList;
    TPixmapIdList mItemList;
    TPixmapIdList mShotList;
    TPixmapIdList mChunkList;
};

#endif // TCATEGORY_H
