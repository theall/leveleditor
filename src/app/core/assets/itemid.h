#ifndef TITEMID_H
#define TITEMID_H

#include <QList>

#include "pixmapid.h"

class TItemId : public TPixmapId
{
public:
    TItemId(int id, TPixmap *pixmap);
    ~TItemId();

private:
};
typedef QList<TItemId*> TItemIdList;

#endif // TITEMID_H
