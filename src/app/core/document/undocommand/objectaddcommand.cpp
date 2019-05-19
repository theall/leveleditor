#include "objectaddcommand.h"
#include "../base/tr.h"

const QString g_commandText[TObjectAddCommand::COUNT] = {
    T("Add %1"),
    T("Remove %1")
};

TObjectAddCommand::TObjectAddCommand(
        Command command,
        TBaseModel *baseModel,
        const TObjectList &objectList,
        const QList<int> &indexList,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mCommand(command)
  , mObjectList(objectList)
  , mBaseModel(baseModel)
  , mIndexList(indexList)
{
    Q_ASSERT(!objectList.isEmpty());

    QString tmp = objectList.at(0)->typeString();
    int objectSize = objectList.size();
    if(objectSize > 1)
        tmp.prepend(QString(" %1 ").arg(objectSize));

    setText(g_commandText[command].arg(tmp));

    if(mIndexList.size() != objectSize)
        mIndexList.clear();

    if(mIndexList.isEmpty()) {
        for(int i=0;i<objectSize;i++) {
            mIndexList.append(-1);
        }
    }
}

TObjectAddCommand::~TObjectAddCommand()
{

}

TObjectAddCommand::Command TObjectAddCommand::command() const
{
    return mCommand;
}

void TObjectAddCommand::undo()
{
    if(mCommand == ADD)
    {
        mIndexList = mBaseModel->removeObjects(mObjectList);
    } else if(mCommand == REMOVE) {
        mBaseModel->insertObjects(mObjectList, mIndexList);
    }
}

void TObjectAddCommand::redo()
{
    if(mCommand == ADD)
    {
        mBaseModel->insertObjects(mObjectList, mIndexList);
    } else if(mCommand == REMOVE) {
        mIndexList = mBaseModel->removeObjects(mObjectList);
    }
}

bool TObjectAddCommand::mergeWith(const QUndoCommand *)
{
    return false;
}
