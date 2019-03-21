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
           const QVariant &parameter = QVariant(),
           QUndoCommand *parent = Q_NULLPTR);
    ~TObjectUndoCommand();

    Command command() const;
    QPointF offset() const;
    TObjectList objectList() const;

private:
    Command mCommand;
    QPointF mOffset;
    TObjectList mObjectList;

    // QUndoCommand interface
public:
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
    bool mergeWith(const QUndoCommand *other) Q_DECL_OVERRIDE;
};

#endif // TOBJECTUNDOCOMMAND_H
