#include "tilesetdock.h"
#include <QToolBar>
#include <QVBoxLayout>
#ifdef GUI_STAND_ALONE
#include <QStringListModel>
#endif

TTilesetDock::TTilesetDock(QWidget *parent) :
    TBaseDock(QLatin1String("TilesetDock"), parent)
{
    CREATE_ACTION(mActionAddTileset, ":/actionsdock/images/add.png", slotAddTilesetTriggered);
    CREATE_ACTION(mActionRemoveTileset, ":/actionsdock/images/remove.png", slotRemoveTilesetTriggered);

    QWidget *container = new QWidget(this);
    mTilesetTab = new TTilesetTab(container);
#ifdef GUI_STAND_ALONE
    for(int i=0;i<10;i++)
    {
        mTilesetTab->addTab(new QStringListModel(this), QString::number(i+1));
    }
#endif
    QToolBar *toolBar = new QToolBar(container);
    toolBar->setFloatable(false);
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(16, 16));
    toolBar->addAction(mActionAddTileset);
    toolBar->addAction(mActionRemoveTileset);

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(toolBar);
    vboxLayout->addWidget(mTilesetTab);
    container->setLayout(vboxLayout);
    setWidget(container);

    retranslateUi();
}

void TTilesetDock::changeEvent(QEvent *e)
{
    QDockWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi();
        break;
    default:
        break;
    }
}

void TTilesetDock::slotAddTilesetTriggered()
{

}

void TTilesetDock::slotRemoveTilesetTriggered()
{

}

TTilesetTab *TTilesetDock::tilesetTab() const
{
    return mTilesetTab;
}

void TTilesetDock::retranslateUi()
{
    setWindowTitle(tr("Tileset"));
}

TTilesetDock::~TTilesetDock()
{

}
