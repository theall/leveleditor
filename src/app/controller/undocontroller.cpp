#include "undocontroller.h"

#include "../gui/component/undodock/undodock.h"

TUndoController::TUndoController(QObject *parent) :
    TAbstractController(parent)
  , mUndoGroup(new QUndoGroup(this))
{
    connect(mUndoGroup, SIGNAL(canUndoChanged(bool)), this, SLOT(slotCanUndoChanged(bool)));
    connect(mUndoGroup, SIGNAL(canRedoChanged(bool)), this, SLOT(slotCanRedoChanged(bool)));
}

TUndoController::~TUndoController()
{

}

bool TUndoController::joint(TMainWindow *mainWindow, TCore *core)
{
    Q_ASSERT(mainWindow);
    Q_ASSERT(core);

    mainWindow->undoDock()->setUndoGroup(mUndoGroup);

    connect(mainWindow, SIGNAL(requestUndo()), this, SLOT(slotRequestUndo()));
    connect(mainWindow, SIGNAL(requestRedo()), this, SLOT(slotRequestRedo()));

    return TAbstractController::joint(mainWindow, core);
}

void TUndoController::setCurrentDocument(TDocument *document)
{
    if(!document)
    {
        mUndoGroup->setActiveStack(nullptr);
        return;
    }
    if(mDocument != document)
    {
        if(mDocument)
            mUndoGroup->removeStack(mDocument->undoStack());

        QUndoStack *undoStack = document->undoStack();
        mUndoGroup->addStack(undoStack);
        mUndoGroup->setActiveStack(undoStack);
    }
}

void TUndoController::slotCanUndoChanged(bool canUndo)
{
    mMainWindow->enableUndoAction(canUndo);
}

void TUndoController::slotCanRedoChanged(bool canRedo)
{
    mMainWindow->enableRedoAction(canRedo);
}

void TUndoController::slotRequestUndo()
{
    mUndoGroup->undo();
}

void TUndoController::slotRequestRedo()
{
    mUndoGroup->redo();
}

void TUndoController::slotTimerEvent()
{

}
