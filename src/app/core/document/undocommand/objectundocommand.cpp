#include "objectundocommand.h"
#include "../base/tr.h"

const QString g_commandText[TObjectUndoCommand::COUNT] = {
    T("Move %s"),
    T("Delete %s")
};

TObjectUndoCommand::TObjectUndoCommand(
        Command command,
        const TObjectList &objectList,
        const QVariant &parameter,
        QUndoCommand *parent) :
    QUndoCommand(parent)
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
    QString tmp = QString("(%d %s)").arg(objectList.size());
    if(objectList.size() > 1)
        tmp.arg(T("objects"));
    else
        tmp.arg(T("object"));
    context += tmp;
    setText(g_commandText[command].arg(context));

    if(command == Move) {
        mOffset = parameter.toPointF();
    }
}

TObjectUndoCommand::~TObjectUndoCommand()
{

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
