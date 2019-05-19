#include "graphicsviewcontexmenu.h"

TGraphicsViewContexMenu::TGraphicsViewContexMenu(QWidget *parent) :
    QMenu(parent)
{
    retranslateUi();
}

TGraphicsViewContexMenu::~TGraphicsViewContexMenu()
{

}

void TGraphicsViewContexMenu::retranslateUi()
{
    actionClone->setText(tr("Clone"));
    actionCopy->setText(tr("Copy"));
    actionPaste->setText(tr("Paste"));
    actionDelete->setText(tr("Delete"));
    actionSetAsStamp->setText(tr("Set stamp"));
    actionSetAsStamp->setToolTip(tr("Set as current tile stamp"));
}
