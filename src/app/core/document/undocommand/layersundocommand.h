#ifndef ACTIONSUNDOCOMMAND_H
#define ACTIONSUNDOCOMMAND_H

#include <QUndoCommand>

enum LayerUndoCommand
{
    LUC_ADD = 0,
    LUC_REMOVE,
    LUC_CLONE,
    LUC_COUNT
};

class TLayer;
class TLayersModel;

class TLayersUndoCommand : public QUndoCommand
{
public:
    TLayersUndoCommand(LayerUndoCommand command, TLayersModel *layersModel, TLayer *layer, QUndoCommand *parent = Q_NULLPTR);
    ~TLayersUndoCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    int mIndex;
    TLayer *mLayer;
    TLayersModel *mLayersModel;
    LayerUndoCommand mCommand;
};

#endif // ACTIONSUNDOCOMMAND_H
