#ifndef TFACEID_H
#define TFACEID_H

#include <QList>

#include "pixmap.h"

class TFaceId
{
public:
    TFaceId();
    TFaceId(int id, TPixmap *pixmap);
    ~TFaceId();

    int id() const;
    void setId(int id);

    TPixmap *pixmap() const;
    void setPixmap(TPixmap *pixmap);

private:
    int mId;
    TPixmap *mPixmap;
};

typedef QList<TFaceId*> TFaceList;
#endif // TFACEID_H
