#ifndef TRECTRESIZEUNDOCOMMAND_H
#define TRECTRESIZEUNDOCOMMAND_H

#include <QMarginsF>
#include <QUndoCommand>

#include "../model/entity/rectobject.h"

class TRectResizeUndoCommand : public QUndoCommand
{
public:
    TRectResizeUndoCommand(
           const TRectObjectList &objectList,
           const QMarginsF &offset = QMarginsF(),
           int commandSequenceId = -1,
           QUndoCommand *parent = Q_NULLPTR);
    ~TRectResizeUndoCommand();


    QMarginsF margin() const;
    void setMargin(const QMarginsF &margin);

    TRectObjectList objectList() const;

private:
    int mId;
    QMarginsF mMargins;
    TRectObjectList mObjectList;

    // QUndoCommand interface
public:
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
    bool mergeWith(const QUndoCommand *other) Q_DECL_OVERRIDE;
    int id() const;
};

#endif // TRECTRESIZEUNDOCOMMAND_H
