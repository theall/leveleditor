#include "movedock.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QFileDialog>

TMoveDock::TMoveDock(QWidget *parent) :
    TBaseDock(QLatin1String("FramesDock"), parent)
  , mPropertyBrowser(new TPropertyBrowser(this))
{
    CREATE_ACTION(mActionNewSoundItem, ":/actionsdock/images/add.png", slotActionNewSoundItemTriggered);
    CREATE_ACTION(mActionRemoveSoundItem, ":/actionsdock/images/remove.png", slotActionRemoveSoundItemTriggered);

    QToolBar *toolBar = new QToolBar(this);
    toolBar->setFloatable(false);
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(16, 16));
    toolBar->addAction(mActionNewSoundItem);
    toolBar->addAction(mActionRemoveSoundItem);

    QWidget *container = new QWidget(this);
    QSplitter *splitter = new QSplitter(this);
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(mPropertyBrowser);
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins(5, 5, 5, 5);
    vBoxLayout->setSpacing(0);
    vBoxLayout->addWidget(toolBar);
    vBoxLayout->addWidget(splitter);
    container->setLayout(vBoxLayout);
    setWidget(container);

    retranslateUi();
}

TMoveDock::~TMoveDock()
{

}

void TMoveDock::slotActionNewSoundItemTriggered()
{
    emit requestAddSoundItems();
}

void TMoveDock::slotActionRemoveSoundItemTriggered()
{

}

void TMoveDock::slotSoundModelValidChanged(bool valid)
{
    mActionNewSoundItem->setEnabled(valid);
}

void TMoveDock::slotSoundItemSelectionChanged(bool hasSelection)
{
    mActionRemoveSoundItem->setEnabled(hasSelection);
}

TPropertyBrowser *TMoveDock::propertyBrowser() const
{
    return mPropertyBrowser;
}

void TMoveDock::retranslateUi()
{
    setWindowTitle(tr("SoundSet"));
    setToolTip(tr("SoundSet edit."));
    mActionNewSoundItem->setToolTip(tr("New Sound item"));
    mActionNewSoundItem->setText(tr("New SoundItem"));
    mActionRemoveSoundItem->setToolTip(tr("Remove sound item."));
    mActionRemoveSoundItem->setText(tr("Remove current sound item"));
}
