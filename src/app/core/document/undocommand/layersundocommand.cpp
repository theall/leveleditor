#include "layersundocommand.h"
#include "../model/layersmodel.h"

#include <QCoreApplication>

#define tr(x) QCoreApplication::translate("UndoCommand", x)

const QString g_commandText[LUC_COUNT] = {
    tr("Add new layer"),
    tr("Remove layer"),
    tr("Clone layer")
};

TLayersUndoCommand::TLayersUndoCommand(
        LayerUndoCommand command,
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
    if(mCommand==LUC_ADD)
    {
        mIndex = mLayersModel->removeLayer(mLayer);
    } else if(mCommand==LUC_REMOVE) {
        mLayersModel->addLayer(mLayer, mIndex);
    }
}

void TLayersUndoCommand::redo()
{
    if(mCommand==LUC_ADD)
    {
        mLayersModel->addLayer(mLayer, mIndex);
    } else if(mCommand==LUC_REMOVE) {
        mIndex = mLayersModel->removeLayer(mLayer);
    }
}
