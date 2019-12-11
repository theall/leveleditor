#include "objectmovecommand.h"
#include "undocommandutils.hpp"
#include "../base/tr.h"

const QString g_commandText = T("Move %1");

TObjectMoveUndoCommand::TObjectMoveUndoCommand(
        const TObjectList &objectList,
        const QPointF &offset,
        int commandSequenceId,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mId(commandSequenceId)
  , mOffset(offset)
  , mObjectList(objectList)
{
    QString context = getContextString(objectList);
    setText(g_commandText.arg(context));
}

TObjectMoveUndoCommand::~TObjectMoveUndoCommand()
{

}

QPointF TObjectMoveUndoCommand::offset() const
{
    return mOffset;
}

TObjectList TObjectMoveUndoCommand::objectList() const
{
    return mObjectList;
}

void TObjectMoveUndoCommand::undo()
{
    for(TObject *object : mObjectList) {
        object->move(-mOffset);
    }
}

void TObjectMoveUndoCommand::redo()
{
    for(TObject *object : mObjectList) {
        object->move(mOffset);
    }
}

bool TObjectMoveUndoCommand::mergeWith(const QUndoCommand *other)
{
    const TObjectMoveUndoCommand *command = static_cast<const TObjectMoveUndoCommand*>(other);
    bool canMerge = command && (mObjectList==command->objectList());
    if(canMerge)
        mOffset += command->offset();
    return canMerge;
}

int TObjectMoveUndoCommand::id() const
{
    return mId;
}
