#ifndef VECTORTABLEUNDOCOMMAND_H
#define VECTORTABLEUNDOCOMMAND_H

#include <QUndoCommand>

enum VectorTableUndoCommand
{
    VTUC_ADD = 0,
    VTUC_REMOVE,
    VTUC_COUNT
};

class TVectorTableModel;
class TVectorItem;

class TVectorTableUndoCommand : public QUndoCommand
{
public:
    TVectorTableUndoCommand(VectorTableUndoCommand command,
                         TVectorTableModel *vectorItemsModel,
                         TVectorItem *vectorItem,
                         QUndoCommand *parent = Q_NULLPTR);
    TVectorTableUndoCommand(VectorTableUndoCommand command,
                         TVectorTableModel *vectorItemsModel,
                         const QList<TVectorItem *> &vectorItemList,
                         QUndoCommand *parent = Q_NULLPTR);
    ~TVectorTableUndoCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    QList<int> mIndexList;
    TVectorTableModel *mVectorItemsModel;
    VectorTableUndoCommand mCommand;
    QList<TVectorItem *> mVectorList;
};

#endif // VECTORTABLEUNDOCOMMAND_H
