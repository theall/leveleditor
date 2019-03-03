#include "sounddock.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QFileDialog>

TSoundDock::TSoundDock(QWidget *parent) :
    TBaseDock(QLatin1String("FramesDock"), parent)
  , mSoundSetView(new TSoundSetView(this))
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
    splitter->addWidget(mSoundSetView);
    splitter->addWidget(mPropertyBrowser);
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setContentsMargins(5, 5, 5, 5);
    vBoxLayout->setSpacing(0);
    vBoxLayout->addWidget(toolBar);
    vBoxLayout->addWidget(splitter);
    container->setLayout(vBoxLayout);
    setWidget(container);

    connect(mSoundSetView,
            SIGNAL(hasSelectionChanged(bool)),
            this,
            SLOT(slotSoundItemSelectionChanged(bool)));
    connect(mSoundSetView,
            SIGNAL(validChanged(bool)),
            this,
            SLOT(slotSoundModelValidChanged(bool)));
    retranslateUi();
}

TSoundDock::~TSoundDock()
{

}

void TSoundDock::slotActionNewSoundItemTriggered()
{
    emit requestAddSoundItems();
}

void TSoundDock::slotActionRemoveSoundItemTriggered()
{
    emit requestRemoveSoundItems(mSoundSetView->getSelectedIndexes());
}

void TSoundDock::slotSoundModelValidChanged(bool valid)
{
    mActionNewSoundItem->setEnabled(valid);
}

void TSoundDock::slotSoundItemSelectionChanged(bool hasSelection)
{
    mActionRemoveSoundItem->setEnabled(hasSelection);
}

TPropertyBrowser *TSoundDock::propertyBrowser() const
{
    return mPropertyBrowser;
}

TSoundSetView *TSoundDock::soundSetView() const
{
    return mSoundSetView;
}

void TSoundDock::retranslateUi()
{
    setWindowTitle(tr("SoundSet"));
    setToolTip(tr("SoundSet edit."));
    mActionNewSoundItem->setToolTip(tr("New Sound item"));
    mActionNewSoundItem->setText(tr("New SoundItem"));
    mActionRemoveSoundItem->setToolTip(tr("Remove sound item."));
    mActionRemoveSoundItem->setText(tr("Remove current sound item"));
}
