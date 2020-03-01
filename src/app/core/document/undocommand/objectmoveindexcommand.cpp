#include "objectmoveindexcommand.h"
#include "undocommandutils.hpp"
#include "../base/tr.h"

const QString g_commandText = T("Move %1");

TObjectMoveIndexCommand::TObjectMoveIndexCommand(
        TBaseModel *baseModel,
        const TObjectList &objectList,
        const QList<int> &indexList,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mBaseModel(baseModel)
  , mObjectList(objectList)
  , mIndexList(indexList)
{
    QString context = getContextString(objectList);
    setText(g_commandText.arg(context));
}

TObjectMoveIndexCommand::~TObjectMoveIndexCommand()
{

}

void TObjectMoveIndexCommand::undo()
{
    mIndexList = mBaseModel->moveObjects(mObjectList, mIndexList);
}

void TObjectMoveIndexCommand::redo()
{
    mIndexList = mBaseModel->moveObjects(mObjectList, mIndexList);
}
