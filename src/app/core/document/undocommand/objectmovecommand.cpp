#include "objectmovecommand.h"
#include "../base/tr.h"

const QString g_commandText = T("Move %1");

TObjectUndoCommand::TObjectUndoCommand(
        const TObjectList &objectList,
        const QPointF &offset,
        int commandSequenceId,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mId(commandSequenceId)
  , mOffset(offset)
  , mObjectList(objectList)
{
    QString context = "";
    TObject::Type lastObjectType = TObject::INVALID;
    for(TObject *object : objectList) {
        if(object->type() != lastObjectType)
        {
            lastObjectType = object->type();
            context += object->typeString() + " ";
            if(context.length() > 10)
                context += "...";
        }
    }
    setText(g_commandText.arg(context));
}

TObjectUndoCommand::~TObjectUndoCommand()
{

}

QPointF TObjectUndoCommand::offset() const
{
    return mOffset;
}

TObjectList TObjectUndoCommand::objectList() const
{
    return mObjectList;
}

void TObjectUndoCommand::undo()
{
    for(TObject *object : mObjectList) {
        object->move(-mOffset);
    }
}

void TObjectUndoCommand::redo()
{
    for(TObject *object : mObjectList) {
        object->move(mOffset);
    }
}

bool TObjectUndoCommand::mergeWith(const QUndoCommand *other)
{
    const TObjectUndoCommand *command = static_cast<const TObjectUndoCommand*>(other);
    bool canMerge = command && (mObjectList==command->objectList());
    if(canMerge)
        mOffset += command->offset();
    return canMerge;
}

int TObjectUndoCommand::id() const
{
    return mId;
}
