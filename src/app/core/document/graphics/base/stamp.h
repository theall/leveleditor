#ifndef TSTAMP_H
#define TSTAMP_H

#include <QPixmap>

class TTileId;
class TFaceId;
class TPixmapId;
class TStamp
{
public:
    TStamp();

    TPixmapId *pixmapId() const;
    TTileId *getTileId() const;
    TFaceId *getFaceId() const;
    void setPixmapId(TPixmapId *pixmapId);

    QPixmap pixmap() const;

private:
    TPixmapId *mPixmapId;
};

#endif // TSTAMP_H
