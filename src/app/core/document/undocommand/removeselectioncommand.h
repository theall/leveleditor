#ifndef TREMOVESELECTIONCOMMAND_H
#define TREMOVESELECTIONCOMMAND_H

#include <QList>
#include <QUndoCommand>
#include "../model/basemodel.h"
#include "../model/entity/object.h"
#include "../graphics/layeritem/layeritem.h"
#include "../graphics/layeritem/objectitem/objectitem.h"
#include "../graphics/uiitem/selecteditems.h"

class TRemoveSelectionCommand : public QUndoCommand
{
public:
    TRemoveSelectionCommand(
           TBaseModel *baseModel,
           TLayerItem *layerItem,
           TSelectedItems *selectedItems,
           QUndoCommand *parent = Q_NULLPTR);
    ~TRemoveSelectionCommand();

private:
    TObjectList mObjectList;
    TBaseModel *mBaseModel;
    QList<int> mIndexList;
    TLayerItem *mLayerItem;
    TObjectItemList mObjectItemList;
    TSelectedItems *mSelectedItems;

    // QUndoCommand interface
public:
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
    bool mergeWith(const QUndoCommand *other) Q_DECL_OVERRIDE;
};

#endif // TREMOVESELECTIONCOMMAND_H
