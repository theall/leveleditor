#ifndef TANIMATIONFRAME_H
#define TANIMATIONFRAME_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TTile;
class TFrame : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TFrame(QObject *parent = nullptr);
    TFrame(TTile *tile, QObject *parent = nullptr);
    ~TFrame();

    int getTileLayer() const;
    int getTileNumber() const;

    TTile *getTile() const;
    QPixmap getPixmap() const;
    int getDuration() const;
    void setTile(TTile *tile);
    void setDuration(int duration);
    void setTileLayer(int tileLayer);
    void setTileNumber(int tileNumber);

private:
    TTile *mTile;
    int mTileLayer;
    int mTileNumber;
    int mDuration;

    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
};

typedef QList<TFrame*> TFrameList;

#endif // TANIMATIONFRAME_H
