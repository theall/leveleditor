#ifndef TTRIGGERID_H
#define TTRIGGERID_H

#include "pixmapid.h"

class TTriggerId : public TPixmapId
{
public:
    TTriggerId(int id, TPixmap *on, TPixmap *off);

    TPixmap *onPixmap() const;
    void setOnPixmap(TPixmap *onPixmap);

    TPixmap *offPixmap() const;
    void setOffPixmap(TPixmap *offPixmap);

private:
    TPixmap *mOnPixmap;
    TPixmap *mOffPixmap;
};
typedef QList<TTriggerId*> TTriggerIdList;

#endif // TTRIGGERID_H
