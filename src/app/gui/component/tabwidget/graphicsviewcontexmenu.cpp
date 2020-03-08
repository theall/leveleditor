#include "graphicsviewcontexmenu.h"

TGraphicsViewContextMenu::TGraphicsViewContextMenu(QWidget *parent) :
    QMenu(parent)
{

    mActionClone = addAction(QString(), this, SLOT(slotActionCloneTriggered()));
    mActionCopy = addAction(QString(), this, SLOT(slotActionCopyTriggered()));
    mActionPaste = addAction(QString(), this, SLOT(slotActionPasteTriggered()));
    mActionDelete = addAction(QString(), this, SLOT(slotActionDeleteTriggered()));
    addSeparator();
    mActionTop = addAction(QString(), this, SLOT(slotActionTopTriggered()));
    mActionLeft = addAction(QString(),this,SLOT(slotActionLeftTriggered()));
    mActionRight = addAction(QString(),this,SLOT(slotActionRightTriggered()));
    mActionDown = addAction(QString(),this,SLOT(slotActionDownTriggered()));
    mActionHorizontal = addAction(QString(),this,SLOT(slotActionHorizontalTriggered()));
    mActionVertical = addAction(QString(),this,SLOT(slotActionVerticalTriggered()));
    addSeparator();
    mActionPlat = addAction(QString(),this,SLOT(slotActionPlatTriggered()));
    mActionBox = addAction(QString(),this,SLOT(slotActionBoxTriggered()));
    mActionArea = addAction(QString(),this,SLOT(slotActionAreaTriggered()));
    mActionDangerArea = addAction(QString(),this,SLOT(slotActionDangerAreaTriggered()));
    mActionClearHeight = addAction(QString(),this,SLOT(slotActionClearHeightTriggered()));

    mActionHorizontal->setCheckable(true);
    mActionVertical->setCheckable(true);
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

void TGraphicsViewContextMenu::slotActionTopTriggered()
{
    emit pressDownTop();
}

void TGraphicsViewContextMenu::slotActionLeftTriggered()
{
    emit pressDownLeft();
}

void TGraphicsViewContextMenu::slotActionRightTriggered()
{
    emit pressDownRight();
}

void TGraphicsViewContextMenu::slotActionDownTriggered()
{
    emit pressDownDown();
}

void TGraphicsViewContextMenu::slotActionHorizontalTriggered()
{
    emit pressDownHorizontal();
}

void TGraphicsViewContextMenu::slotActionVerticalTriggered()
{
    emit pressDownVertical();
}

void TGraphicsViewContextMenu::slotActionPlatTriggered()
{
    emit pressDownPlat();
}

void TGraphicsViewContextMenu::slotActionBoxTriggered()
{
    emit pressDownBox();
}

void TGraphicsViewContextMenu::slotActionAreaTriggered()
{
    emit pressDownArea();
}

void TGraphicsViewContextMenu::slotActionDangerAreaTriggered()
{
    emit pressDownDangerArea();
}

void TGraphicsViewContextMenu::slotActionClearHeightTriggered()
{
    emit pressDownClearHeight();
}

void TGraphicsViewContextMenu::retranslateUi()
{
    mActionClone->setText(tr("Clone"));
    mActionCopy->setText(tr("Copy"));
    mActionPaste->setText(tr("Paste"));
    mActionDelete->setText(tr("Delete"));
    mActionTop->setText(tr("Align Top"));
    mActionLeft->setText(tr("Align Left"));
    mActionRight->setText(tr("Align Right"));
    mActionDown->setText(tr("Align Down"));
    mActionHorizontal->setText(tr("Arrange Horizontal"));
    mActionVertical->setText(tr("Arrange Vertical"));
    mActionPlat->setText(tr("Add Plat"));
    mActionBox->setText(tr("Add Box"));
    mActionArea->setText(tr("Add Area"));
    mActionDangerArea->setText(tr("Danger Area"));
    mActionClearHeight->setText(tr("Clear Height"));
}

