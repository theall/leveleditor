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
    setPropertyBrowser(mainWindow->propertyDock()->propertyBrowser());
    return ret;
}

void TMainPropertyController::setPropertySheet(TPropertySheet *propertySheet)
{
    TPropertyController::setPropertySheet(propertySheet);
    mMainWindow->propertyDock()->setText(propertySheet!=nullptr?propertySheet->getContextName():"");
}

void TMainPropertyController::setCurrentDocument(TDocument *document)
{
    if(mDocument==document)
        return;

    if(document)
    {
        TPropertySheet *propertySheet = document->propertySheet();
        if(!propertySheet)
            return;

        setPropertySheet(document->propertySheet());
    } else {
        setPropertySheet(nullptr);
    }
}
