#ifndef TBORNPOSITEM_H
#define TBORNPOSITEM_H

#include "playeritem.h"

class TRespawn;
class TBornPosItem : public TPlayerItem
{
    Q_OBJECT

public:
    TBornPosItem(TRespawn *respawn,QGraphicsItem *parent = Q_NULLPTR);
    ~TBornPosItem();

    TRespawn *respawn() const;

private:
    TRespawn *mRespawn;

public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};
typedef QList<TBornPosItem*> TBornPosItemList;

#endif // TBORNPOSITEM_H
