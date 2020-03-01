#ifndef TOBJECTMOVEINDEXCOMMAND_H
#define TOBJECTMOVEINDEXCOMMAND_H

#include <QList>
#include <QUndoCommand>
#include "../model/basemodel.h"
#include "../model/entity/object.h"

class TObjectMoveIndexCommand : public QUndoCommand
{
public:
    TObjectMoveIndexCommand(
                            TBaseModel *baseModel,
                            const TObjectList &objectList,
                            const QList<int> &indexList,
                            QUndoCommand *parent = Q_NULLPTR);
    ~TObjectMoveIndexCommand();

private:
    TBaseModel *mBaseModel;
    TObjectList mObjectList;
    QList<int> mIndexList;


public:
    void undo();
    void redo();
};

#endif // TOBJECTMOVEINDEXCOMMAND_H
