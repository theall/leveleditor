#include "mainpropertycontroller.h"
#include "../gui/component/propertydock/propertiesdock.h"

TMainPropertyController::TMainPropertyController(QObject *parent) :
    TPropertyController(parent)
{

}

TMainPropertyController::~TMainPropertyController()
{

}

bool TMainPropertyController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);

    bool ret = TPropertyController::joint(mainWindow, core);
    setPropertyBrowser(mainWindow->getPropertyDock()->propertyBrowser());
    return ret;
}

void TMainPropertyController::setPropertySheet(TPropertySheet *propertySheet)
{
    TPropertyController::setPropertySheet(propertySheet);
    mMainWindow->getPropertyDock()->setText(propertySheet?propertySheet->getContextName():"");
}

void TMainPropertyController::setCurrentDocument(TDocument *document)
{
    if(mDocument == document)
        return;

    if(mDocument)
        mDocument->disconnect(this);

    TPropertySheet *propertySheet = nullptr;
    if(document)
    {
        TGraphicsScene *graphicsScene = document->graphicsScene();
        connect(graphicsScene, SIGNAL(selectedObjectChanged(TObject*,TObject*)), this, SLOT(slotOnSelectedObjectChanged(TObject*,TObject*)));
        TObjectItem *lastSelectedObject = graphicsScene->getLastSelectedObjectItem();
        propertySheet = lastSelectedObject?lastSelectedObject->object()->propertySheet():document->getSceneModel()->propertySheet();

    }
    setPropertySheet(propertySheet);
}

void TMainPropertyController::slotOnSelectedObjectChanged(TObject *, TObject *current)
{
    TPropertySheet *propertySheet = nullptr;
    if(current) {
        propertySheet = current->propertySheet();
    } else {
        propertySheet = mDocument?mDocument->getSceneModel()->propertySheet():nullptr;
    }
    setPropertySheet(propertySheet);
}
