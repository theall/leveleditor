#ifndef TOBJECTADDCOMMAND_H
#define TOBJECTADDCOMMAND_H

#include <QList>
#include <QUndoCommand>
#include "../model/basemodel.h"
#include "../model/entity/object.h"

class TObjectAddCommand : public QUndoCommand
{
public:
    enum Command {
        ADD,
        REMOVE,
        COUNT
    };

    TObjectAddCommand(
           Command command,
           TBaseModel *model,
           const TObjectList &objectList,
           const QList<int> &indexList = QList<int>(),
           QUndoCommand *parent = Q_NULLPTR);

    ~TObjectAddCommand();

    Command command() const;

private:
    Command mCommand;
    TObjectList mObjectList;
    TBaseModel *mBaseModel;
    QList<int> mIndexList;

    // QUndoCommand interface
public:
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
    bool mergeWith(const QUndoCommand *other) Q_DECL_OVERRIDE;
};

#endif // TOBJECTADDCOMMAND_H
