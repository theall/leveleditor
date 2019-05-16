#ifndef TOBJECTUNDOCOMMAND_H
#define TOBJECTUNDOCOMMAND_H

#include <QPointF>
#include <QUndoCommand>
#include "../model/entity/object.h"

class TObjectUndoCommand : public QUndoCommand
{
public:
    TObjectUndoCommand(
           const TObjectList &objectList,
           const QPointF &offset = QPointF(),
           int commandSequenceId = -1,
           QUndoCommand *parent = Q_NULLPTR);
    ~TObjectUndoCommand();

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

#endif // TOBJECTUNDOCOMMAND_H
