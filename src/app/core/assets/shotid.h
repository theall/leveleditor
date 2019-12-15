#ifndef TSHOTID_H
#define TSHOTID_H

#include "pixmapid.h"

#include <QList>

class TShotId : public TPixmapId
{
public:
    TShotId(int id, TPixmap *pixmap);
    ~TShotId();
};
typedef QList<TShotId*> TShotList;

#endif // TSHOTID_H
