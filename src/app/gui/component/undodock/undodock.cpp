#include "undodock.h"

#include <QEvent>
#include <QUndoView>
#include <QVBoxLayout>

TUndoDock::TUndoDock(QWidget *parent)
    : TBaseDock(QLatin1String("UndoViewDock"), parent)
{
    mUndoView = new QUndoView(this);
    mUndoView->setFrameShape(QFrame::Panel);
    mUndoView->setFrameShadow(QFrame::Sunken);
    QIcon cleanIcon(QLatin1String(":/undodock/images/empty.png"));
    mUndoView->setCleanIcon(cleanIcon);
    mUndoView->setUniformItemSizes(true);

    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setMargin(5);
    layout->addWidget(mUndoView);

    setWidget(widget);
    retranslateUi();
}

TUndoDock::~TUndoDock()
{

}

void TUndoDock::setUndoGroup(QUndoGroup *undoGroup)
{
    if(mUndoView)
        mUndoView->setGroup(undoGroup);
}

void TUndoDock::retranslateUi()
{
    setWindowTitle(tr("History"));
    mUndoView->setEmptyLabel(tr("<empty>"));
}
