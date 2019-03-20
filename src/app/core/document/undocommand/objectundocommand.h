#ifndef TOBJECTUNDOCOMMAND_H
#define TOBJECTUNDOCOMMAND_H

#include <QPointF>
#include <QUndoCommand>
#include "../model/entity/object.h"

class TObjectUndoCommand : public QUndoCommand
{
public:
    enum Command
    {
        Move = 0,
        Delete,
        COUNT
    };

    TObjectUndoCommand(
           Command command,
           const TObjectList &objectList,
           const QVariant &parameter,
           QUndoCommand *parent = Q_NULLPTR);
    ~TObjectUndoCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    Command mCommand;
    QPointF mOffset;
    TObjectList mObjectList;
};

#endif // TOBJECTUNDOCOMMAND_H
