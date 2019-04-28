#ifndef TDAREAITEM_H
#define TDAREAITEM_H

#include "objectitem.h"
#include "../../../model/entity/darea.h"

class TDAreaItem : public TObjectItem
{
    Q_OBJECT

public:
    TDAreaItem(TDArea *darea, QGraphicsItem *parent = Q_NULLPTR);
    ~TDAreaItem();

    TDArea *darea() const;

private:
    TDArea *mDArea;

    // TObjectItem interface
public:
    void propertyValueChanged(PropertyID pid) Q_DECL_OVERRIDE;
};
typedef QList<TDAreaItem*> TDAreaItemList;

#endif // TDAREAITEM_H
