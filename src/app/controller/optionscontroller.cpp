#include "optionscontroller.h"

#include "../utils/preferences.h"

TOptionsController::TOptionsController(QObject *parent) :
    TAbstractController(parent)
{

}

TOptionsController::~TOptionsController()
{

}

bool TOptionsController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    return TAbstractController::joint(mainWindow, core);
}

void TOptionsController::setCurrentDocument(TDocument *document)
{
    Q_UNUSED(document);
}

void TOptionsController::slotTimerEvent()
{
}
