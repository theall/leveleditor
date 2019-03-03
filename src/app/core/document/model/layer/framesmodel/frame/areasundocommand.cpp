#include "areasundocommand.h"
#include "area.h"

#include <QCoreApplication>

#define tr(x) QCoreApplication::translate("UndoCommand", x)

const QString g_commandText[AUC_COUNT] = {
    tr("Add %1 %2 area"),
    tr("Remove %1 %2 area(s)"),
    tr("Move %1 %2 area(s)")
};

TAreasUndoCommand::TAreasUndoCommand(
        AreasUndoCommand command,
        TAreaManager *areaManager,
        TArea *area,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mAreaManager(areaManager)
  , mCommand(command)
{
    Q_ASSERT(areaManager);
    Q_ASSERT(area);

    mAreaList.append(area);
    setText(g_commandText[command].arg(1).arg(areaManager->areaTypeString()));
}

TAreasUndoCommand::TAreasUndoCommand(
        AreasUndoCommand command,
        TAreaManager *areaManager,
        const QList<TArea *> &areaList,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mAreaManager(areaManager)
  , mCommand(command)
  , mAreaList(areaList)
{
    Q_ASSERT(areaManager);

    setText(g_commandText[command].arg(areaList.size()).arg(areaManager->areaTypeString()));
}

TAreasUndoCommand::TAreasUndoCommand(
        AreasUndoCommand command,
        TAreaManager *areaManager,
        const QList<TArea *> &areaList,
        const QPointF &distance,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mAreaManager(areaManager)
  , mCommand(command)
  , mAreaList(areaList)
  , mMoveDistance(distance)
{
    Q_ASSERT(areaManager);
    Q_ASSERT(!distance.isNull());
    setText(g_commandText[command].arg(areaList.size()).arg(areaManager->areaTypeString()));
}

TAreasUndoCommand::~TAreasUndoCommand()
{

}

void TAreasUndoCommand::undo()
{
    if(mCommand==AUC_ADD)
    {
        mAreaList = mAreaManager->remove(mAreaList);
    } else if(mCommand==AUC_REMOVE) {
        mAreaManager->add(mAreaList);
    } else if(mCommand==AUC_MOVE) {
        mAreaManager->move(mAreaList, -mMoveDistance);
    }
}

void TAreasUndoCommand::redo()
{
    if(mCommand==AUC_ADD)
    {
        mAreaManager->add(mAreaList);
    } else if(mCommand==AUC_REMOVE) {
        mAreaList = mAreaManager->remove(mAreaList);
    } else if(mCommand==AUC_MOVE) {
        mAreaManager->move(mAreaList, mMoveDistance);
    }
}

QPointF TAreasUndoCommand::moveDistance() const
{
    return mMoveDistance;
}

QList<TArea *> TAreasUndoCommand::areaList() const
{
    return mAreaList;
}

int TAreasUndoCommand::id() const
{
    return mCommand;
}

bool TAreasUndoCommand::mergeWith(const QUndoCommand *other)
{
    if(mCommand==AUC_MOVE && mCommand==other->id())
    {
        const TAreasUndoCommand *areasUndoCommand = static_cast<const TAreasUndoCommand *>(other);
        if(areasUndoCommand)
        {
            QPointF otherMoveDistance = areasUndoCommand->moveDistance();
            TAreaList otherAreaList = areasUndoCommand->areaList();
            if(mAreaList==otherAreaList) {
                mMoveDistance += otherMoveDistance;
                return true;
            } else if(mMoveDistance==otherMoveDistance) {
                mAreaList = mAreaList.toSet().unite(otherAreaList.toSet()).toList();
                setText(g_commandText[mCommand].arg(mAreaList.size()).arg(mAreaManager->areaTypeString()));
                return true;
            }
        }
    }
    return false;
}

