#ifndef TPIXMAPID_H
#define TPIXMAPID_H

#include "pixmap.h"

class TPixmapId
{
public:
    TPixmapId(int id, TPixmap *pixmap);
    ~TPixmapId();

    int id() const;
    void setId(int id);

    TPixmap *pixmap() const;
    void setPixmap(TPixmap *pixmap);

    QPixmap primitive() const;

private:
    int mId;
    TPixmap *mPixmap;
};
typedef QList<TPixmapId*> TPixmapIdList;

#endif // TPIXMAPID_H
