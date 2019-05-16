#ifndef TTILEUNDOCOMMAND_H
#define TTILEUNDOCOMMAND_H

#include <QList>
#include <QUndoCommand>
#include "../model/entity/layer.h"

class TTileUndoCommand : public QUndoCommand
{
public:
    enum Command
    {
        ADD = 0,
        REMOVE,
        COUNT
    };

    TTileUndoCommand(
           Command command,
           TLayer *layer,
           TTile *tile,
           int index,
           QUndoCommand *parent = Q_NULLPTR);

    TTileUndoCommand(
           Command command,
           TLayer *layer,
           const TTileList tileList,
           const QList<int> &indexList = QList<int>(),
           QUndoCommand *parent = Q_NULLPTR);
    ~TTileUndoCommand();

    Command command() const;

private:
    int mId;
    Command mCommand;
    TLayer *mLayer;
    TTileList mTileList;
    QList<int> mTileIndexList;

    // QUndoCommand interface
public:
    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;
    bool mergeWith(const QUndoCommand *other) Q_DECL_OVERRIDE;
    int id() const;
};

#endif // TTILEUNDOCOMMAND_H
