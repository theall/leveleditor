#include "layerscontroller.h"
#include "gui/component/layerdock/layerdock.h"
#include "gui/component/layerdock/layerview.h"

TLayersController::TLayersController(QObject *parent) :
    TAbstractController(parent)
  , mLayerView(nullptr)
{

}

TLayersController::~TLayersController()
{

}

bool TLayersController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    mLayerView = mainWindow->getLayerDock()->layerView();
    connect(mLayerView, SIGNAL(currentRowChanged(int)), this, SLOT(slotCurrentLayerSelected(int)));

    return TAbstractController::joint(mainWindow, core);
}

void TLayersController::setCurrentDocument(TDocument *document)
{
    if(mDocument == document)
        return;

    if(mDocument)
        mDocument->disconnect(this);

    QAbstractItemModel *model = nullptr;

    if(document)
    {
        model = document->getSceneModel();
    }
    mLayerView->setModel(model);
}

void TLayersController::slotCurrentLayerSelected(int row)
{
    if(!mDocument)
        return;

//    TGraphicsScene *graphicsScene = mDocument->graphicsScene();
//    TLayerItemList layerItemList = graphicsScene->getLayerItemList();
//    TLayerItem *layerItem = graphicsScene->getLayerItem(row);
//    if(!layerItem) {
//        for(TLayerItem *_layerItem : layerItemList)
//            _layerItem->setOpacity(1.0);
//        return;
//    }

//    int i = 0;
//    for(TLayerItem *_layerItem : layerItemList) {
//        if(i > row) {
//            _layerItem->setOpacity(0);
//        } else if(i < row) {
//            _layerItem->setOpacity(0.1);
//        }
//        i++;
//    }
//    layerItem->setOpacity(1.0);
}

void TLayersController::slotTimerEvent()
{

}
