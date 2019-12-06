#ifndef TSHOTID_H
#define TSHOTID_H

#include "pixmapid.h"

class TShotId : public TPixmapId
{
public:
    TShotId(int id, TPixmap *pixmap);
};
typedef QList<TShotId*> TShotList;

#endif // TSHOTID_H
