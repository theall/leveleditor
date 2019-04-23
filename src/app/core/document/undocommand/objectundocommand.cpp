#include "objectundocommand.h"
#include "../base/tr.h"

const QString g_commandText[TObjectUndoCommand::COUNT] = {
    T("Move %1"),
    T("Delete %1")
};

TObjectUndoCommand::TObjectUndoCommand(
        Command command,
        const TObjectList &objectList,
        const QVariant &parameter,
        int commandSequenceId,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mId(commandSequenceId)
  , mCommand(command)
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
    setText(g_commandText[command].arg(context));

    if(command == Move) {
        mOffset = parameter.toPointF();
    }
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

TObjectUndoCommand::Command TObjectUndoCommand::command() const
{
    return mCommand;
}

void TObjectUndoCommand::undo()
{
    if(mCommand==Move)
    {
        for(TObject *object : mObjectList) {
            object->move(-mOffset);
        }
    }
}

void TObjectUndoCommand::redo()
{
    if(mCommand==Move)
    {
       for(TObject *object : mObjectList) {
           object->move(mOffset);
       }
    }
}

bool TObjectUndoCommand::mergeWith(const QUndoCommand *other)
{
    const TObjectUndoCommand *command = static_cast<const TObjectUndoCommand*>(other);
    bool canMerge = command && (mCommand==command->command()) && (mObjectList==command->objectList());
    if(canMerge)
        mOffset += command->offset();
    return canMerge;
}

int TObjectUndoCommand::id() const
{
    return mId;
}
