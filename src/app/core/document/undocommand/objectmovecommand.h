#ifndef TOBJECTMOVEUNDOCOMMAND_H
#define TOBJECTMOVEUNDOCOMMAND_H

#include <QPointF>
#include <QUndoCommand>
#include "../model/entity/object.h"

class TObjectMoveUndoCommand : public QUndoCommand
{
public:
    TObjectMoveUndoCommand(
           const TObjectList &objectList,
           const QPointF &offset = QPointF(),
           int commandSequenceId = -1,
           QUndoCommand *parent = Q_NULLPTR);
    ~TObjectMoveUndoCommand();

    QPointF offset() const;
    TObjectList objectList() const;

private:
    int mId;
    QPointF mOffset;
    TObjectList mObjectList;

    // QUndoCommand interface
public:
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
    bool mergeWith(const QUndoCommand *other) Q_DECL_OVERRIDE;
    int id() const;
};

#endif // TOBJECTMOVEUNDOCOMMAND_H
