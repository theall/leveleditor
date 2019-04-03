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
    mMainWindow->getPropertyDock()->setText(propertySheet!=nullptr?propertySheet->getContextName():"");
}

void TMainPropertyController::setCurrentDocument(TDocument *document)
{
    if(mDocument == document)
        return;

    if(mDocument)
        mDocument->disconnect(this);

    if(document)
    {
        connect(document->graphicsScene(), SIGNAL(selectedObjectChanged(TObject*,TObject*)), this, SLOT(slotOnSelectedObjectChanged(TObject*,TObject*)));
        TPropertySheet *propertySheet = document->propertySheet();
        if(!propertySheet)
            return;

        setPropertySheet(document->propertySheet());

    } else {
        setPropertySheet(nullptr);
    }
}

void TMainPropertyController::slotOnSelectedObjectChanged(TObject *, TObject *current)
{
    if(current)
        setPropertySheet(current->propertySheet());
}
