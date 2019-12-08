#ifndef TRESPOWNPOSITEM_H
#define TRESPOWNPOSITEM_H

#include "playeritem.h"

class TRespawn;
class TRespownPosItem : public TPlayerItem
{
    Q_OBJECT

public:
    TRespownPosItem(TRespawn *respawn, QGraphicsItem *parent = Q_NULLPTR);
    ~TRespownPosItem();

    TRespawn *respawn() const;

private:
    QPoint pos;
    TRespawn *mRespawn;

public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};
typedef QList<TRespownPosItem*> TRespownPosItemList;

#endif // TRESPOWNPOSITEM_H
