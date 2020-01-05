#include "graphicsviewcontexmenu.h"

TGraphicsViewContextMenu::TGraphicsViewContextMenu(QWidget *parent) :
    QMenu(parent)
{
    mActionClone = addAction(QString(), this, SLOT(slotActionCloneTriggered()));
    mActionCopy = addAction(QString(), this, SLOT(slotActionCopyTriggered()));
    mActionPaste = addAction(QString(), this, SLOT(slotActionPasteTriggered()));
    mActionDelete = addAction(QString(), this, SLOT(slotActionDeleteTriggered()));

    mActionPaste->setDisabled(true);

    retranslateUi();
}

TGraphicsViewContextMenu::~TGraphicsViewContextMenu()
{

}

void TGraphicsViewContextMenu::setActionCloneState(bool state)
{
    mActionClone->setDisabled(state);
}

void TGraphicsViewContextMenu::setActionCopyState(bool state)
{
    mActionCopy->setDisabled(state);
}

void TGraphicsViewContextMenu::setActionPasteState(bool state)
{
    mActionPaste->setDisabled(state);
}

void TGraphicsViewContextMenu::setActionDeleteState(bool state)
{
    mActionDelete->setDisabled(state);
}

void TGraphicsViewContextMenu::setAllActionsState(bool state)
{
    setActionCloneState(state);
    setActionCopyState(state);
    setActionDeleteState(state);
}

void TGraphicsViewContextMenu::slotActionCloneTriggered()
{
    emit pressDownClone();
}

void TGraphicsViewContextMenu::slotActionCopyTriggered()
{
    emit pressDownCopy();
}

void TGraphicsViewContextMenu::slotActionPasteTriggered()
{
    emit pressDownPaste();
}

void TGraphicsViewContextMenu::slotActionDeleteTriggered()
{
    emit pressDownDelete();
    setAllActionsState(true);
}

void TGraphicsViewContextMenu::retranslateUi()
{
    mActionClone->setText(tr("Clone"));
    mActionCopy->setText(tr("Copy"));
    mActionPaste->setText(tr("Paste"));
    mActionDelete->setText(tr("Delete"));
}
