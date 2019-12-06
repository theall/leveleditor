#ifndef TFACEID_H
#define TFACEID_H

#include <QList>

#include "pixmapid.h"

class TFaceId : public TPixmapId
{
public:
    TFaceId(int id, TPixmap *pixmap);
    ~TFaceId();

private:
};
typedef QList<TFaceId*> TFaceList;

#endif // TFACEID_H
