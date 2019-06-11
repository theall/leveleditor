#ifndef TANIMATION_H
#define TANIMATION_H

#include <QList>

#include "object.h"
#include "frame.h"
#include "../../base/io.h"

class TTile;
class TAnimation : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TAnimation(QObject *parent = nullptr);
    ~TAnimation();

    TFrameList frameList() const;
    void setFrameList(const TFrameList &frameList);

    int getTileLayer() const;
    int getTileNumber() const;
    QPixmap getIcon() const;
    TTile *getTile() const;
    void setTile(TTile *tile);

private:
    TTile *mTile;
    int mTileLayer;
    int mTileNumber;
    TFrameList mFrameList;
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

typedef QList<TAnimation*> TAnimationList;
#endif // TANIMATION_H
