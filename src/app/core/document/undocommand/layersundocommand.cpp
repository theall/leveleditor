#include "layersundocommand.h"
#include "../model/layersmodel.h"
#include "../base/tr.h"

const QString g_commandText[TLayersUndoCommand::COUNT] = {
    T("Add new layer"),
    T("Remove layer"),
    T("Clone layer")
};

TLayersUndoCommand::TLayersUndoCommand(
        Command command,
        TLayersModel *layerModel,
        TLayer *layer,
        QUndoCommand *parent) :
    QUndoCommand(parent)
  , mIndex(-1)
  , mLayer(layer)
  , mLayersModel(layerModel)
  , mCommand(command)
{
    setText(g_commandText[command]);
}

TLayersUndoCommand::~TLayersUndoCommand()
{

}

void TLayersUndoCommand::undo()
{
    if(mCommand==Add)
    {
        mIndex = mLayersModel->removeLayer(mLayer);
    } else if(mCommand==Remove) {
        mLayersModel->addLayer(mLayer, mIndex);
    }
}

void TLayersUndoCommand::redo()
{
    if(mCommand==Add)
    {
        mLayersModel->addLayer(mLayer, mIndex);
    } else if(mCommand==Remove) {
        mIndex = mLayersModel->removeLayer(mLayer);
    }
}
