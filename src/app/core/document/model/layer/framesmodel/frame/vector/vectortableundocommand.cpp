#include "vectoritem.h"
#include "vectortablemodel.h"
#include "vectortableundocommand.h"

#include <QCoreApplication>

#define tr(x) QCoreApplication::translate("UndoCommand", x)

const QString g_commandText[VTUC_COUNT] = {
    tr("Add %1 vector item(s)"),
    tr("Remove %1 vector item(s)")
};

TVectorTableUndoCommand::TVectorTableUndoCommand(
        VectorTableUndoCommand command,
        TVectorTableModel *vectorItemsModel,
        TVectorItem *vectorItem,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mVectorItemsModel(vectorItemsModel)
  , mCommand(command)
{
    mVectorList.append(vectorItem);
    setText(g_commandText[command].arg(1));
}

TVectorTableUndoCommand::TVectorTableUndoCommand(
        VectorTableUndoCommand command,
        TVectorTableModel *vectorItemsModel,
        const QList<TVectorItem *> &vectorItemList,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mVectorItemsModel(vectorItemsModel)
  , mCommand(command)
  , mVectorList(vectorItemList)
{
    setText(g_commandText[command].arg(mVectorList.size()));
}

TVectorTableUndoCommand::~TVectorTableUndoCommand()
{

}

void TVectorTableUndoCommand::undo()
{
    if(mCommand==VTUC_ADD)
    {
        mIndexList = mVectorItemsModel->removeVectorItemList(mVectorList);
    } else if(mCommand==VTUC_REMOVE) {
        mVectorItemsModel->addVectorItemList(mVectorList, mIndexList);
    }
}

void TVectorTableUndoCommand::redo()
{
    if(mCommand==VTUC_ADD)
    {
        mVectorItemsModel->addVectorItemList(mVectorList, mIndexList);
    } else if(mCommand==VTUC_REMOVE) {
        mIndexList = mVectorItemsModel->removeVectorItemList(mVectorList);
    }
}
