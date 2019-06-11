#include "removeselectioncommand.h"
#include "../base/tr.h"

TRemoveSelectionCommand::TRemoveSelectionCommand(
        TBaseModel *baseModel,
        TLayerItem *layerItem,
        TSelectedItems *selectedItems,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mBaseModel(baseModel)
  , mLayerItem(layerItem)
  , mSelectedItems(selectedItems)
{
    Q_ASSERT(mLayerItem);
    Q_ASSERT(mBaseModel);
    Q_ASSERT(mSelectedItems);

    mObjectList = mSelectedItems->getSelectedObjectList();

    Q_ASSERT(!mObjectList.isEmpty());
    QString tmp = mObjectList.at(0)->typeString();
    int objectSize = mObjectList.size();
    if(objectSize > 1)
        tmp.prepend(QString(" %1 ").arg(objectSize));

    setText(T("Remove %1").arg(tmp));
}

TRemoveSelectionCommand::~TRemoveSelectionCommand()
{

}

void TRemoveSelectionCommand::undo()
{
    mBaseModel->insertObjects(mObjectList, mIndexList);
    TObjectItemList objectItemList;
    for(TObjectItem *objectItem : mLayerItem->getObjectItemList()) {
        if(mObjectList.contains(objectItem->object())) {
            objectItemList.append(objectItem);
        }
    }
    mSelectedItems->setObjectItemList(objectItemList);
}

void TRemoveSelectionCommand::redo()
{
    mIndexList = mBaseModel->removeObjects(mObjectList);
    mSelectedItems->clear();
}

bool TRemoveSelectionCommand::mergeWith(const QUndoCommand *)
{
    return false;
}

