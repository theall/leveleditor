#ifndef ACTIONSUNDOCOMMAND_H
#define ACTIONSUNDOCOMMAND_H

#include <QUndoCommand>

class TLayer;
class TLayersModel;

class TLayersUndoCommand : public QUndoCommand
{
public:
    enum Command
    {
        Add = 0,
        Remove,
        Clone,
        COUNT
    };

    TLayersUndoCommand(Command command, TLayersModel *layersModel, TLayer *layer, QUndoCommand *parent = Q_NULLPTR);
    ~TLayersUndoCommand();

    void undo() Q_DECL_OVERRIDE;
    void redo() Q_DECL_OVERRIDE;

private:
    int mIndex;
    TLayer *mLayer;
    TLayersModel *mLayersModel;
    Command mCommand;
};

#endif // ACTIONSUNDOCOMMAND_H
