#include "rectresizeundocommand.h"
#include "undocommandutils.hpp"

#include "../base/tr.h"

const QString g_commandText = T("Resize %1");

TRectResizeUndoCommand::TRectResizeUndoCommand(
        const TRectObjectList &objectList,
        const QMarginsF &margins,
        int commandSequenceId,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mId(commandSequenceId)
  , mMargins(margins)
  , mObjectList(objectList)
{
    QString context = getContextString<TRectObject*>(objectList);
    setText(g_commandText.arg(context));
}

TRectResizeUndoCommand::~TRectResizeUndoCommand()
{

}

TRectObjectList TRectResizeUndoCommand::objectList() const
{
    return mObjectList;
}

QMarginsF TRectResizeUndoCommand::margin() const
{
    return mMargins;
}

void TRectResizeUndoCommand::setMargin(const QMarginsF &margin)
{
    mMargins = margin;
}

void TRectResizeUndoCommand::undo()
{
    for(TRectObject *object : mObjectList) {
        object->adjust(-mMargins);
    }
}

void TRectResizeUndoCommand::redo()
{
    for(TRectObject *object : mObjectList) {
        object->adjust(mMargins);
    }
}

bool TRectResizeUndoCommand::mergeWith(const QUndoCommand *other)
{
    const TRectResizeUndoCommand *command = static_cast<const TRectResizeUndoCommand*>(other);
    bool canMerge = command && (mObjectList==command->objectList());
    if(canMerge)
        mMargins += command->margin();
    return canMerge;
}

int TRectResizeUndoCommand::id() const
{
    return mId;
}
