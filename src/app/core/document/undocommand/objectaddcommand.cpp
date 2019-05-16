#include "objectaddcommand.h"
#include "../base/tr.h"

const QString g_commandText[TTileUndoCommand::COUNT] = {
    T("Add tile"),
    T("Remove tile")
};

TTileUndoCommand::TTileUndoCommand(
        Command command,
        TLayer *layer,
        TTile *tile,
        int index,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mCommand(command)
  , mLayer(layer)
{
    mTileList.append(tile);
    mTileIndexList.append(index);
    setText(g_commandText[command]);
}

TTileUndoCommand::TTileUndoCommand(
        Command command,
        TLayer *layer,
        const TTileList tileList,
        const QList<int> &indexList,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mCommand(command)
  , mLayer(layer)
  , mTileList(tileList)
  , mTileIndexList(indexList)
{
    setText(g_commandText[command]);

    if(mTileIndexList.size() != mTileList.size())
        mTileIndexList.clear();

    if(mTileIndexList.isEmpty()) {
        for(int i=0;i<tileList.size();i++) {
            mTileIndexList.append(-1);
        }
    }
}

TTileUndoCommand::~TTileUndoCommand()
{

}

TTileUndoCommand::Command TTileUndoCommand::command() const
{
    return mCommand;
}

void TTileUndoCommand::undo()
{
    if(mCommand == ADD)
    {

    }
}

void TTileUndoCommand::redo()
{
    if(mCommand == REMOVE)
    {

    }
}

bool TTileUndoCommand::mergeWith(const QUndoCommand *)
{
    return false;
}

int TTileUndoCommand::id() const
{
    return mId;
}
