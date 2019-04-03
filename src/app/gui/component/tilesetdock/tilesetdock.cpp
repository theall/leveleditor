#include "tilesetdock.h"
#include <QToolBar>
#include <QVBoxLayout>

TTileSetDock::TTileSetDock(QWidget *parent) :
    TBaseDock(QLatin1String("TileSetDock"), parent)
{
    CREATE_ACTION(mActionAddTileset, ":/actionsdock/images/add.png", slotAddTilesetTriggered);
    CREATE_ACTION(mActionRemoveTileset, ":/actionsdock/images/remove.png", slotRemoveTilesetTriggered);

    QWidget *container = new QWidget(this);
    mTilesetTab = new TTilesetTab(container);
#ifdef GUI_STAND_ALONE
    for(int i=0;i<10;i++)
    {
        mTilesetTab->addTab((void*)(i+0x10000), QString::number(i));
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

void TTileSetDock::changeEvent(QEvent *e)
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

void TTileSetDock::slotAddTilesetTriggered()
{

}

void TTileSetDock::slotRemoveTilesetTriggered()
{

}

void TTileSetDock::retranslateUi()
{
    setWindowTitle(tr("TileSet"));
}

TTileSetDock::~TTileSetDock()
{

}
