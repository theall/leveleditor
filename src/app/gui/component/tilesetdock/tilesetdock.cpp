#include "tilesetdock.h"
#include <QToolBar>
#include <QVBoxLayout>
#ifdef GUI_STAND_ALONE
#include <QStringListModel>
#endif

TTilesetDock::TTilesetDock(QWidget *parent) :
    TBaseDock(QLatin1String("TilesetDock"), parent)
{
    CREATE_ACTION(mActionAddTileset, ":/animationdock/images/add.png", slotAddTilesetTriggered);
    CREATE_ACTION(mActionRemoveTileset, ":/animationdock/images/remove.png", slotRemoveTilesetTriggered);

    QWidget *container = new QWidget(this);
    mTilesetTab = new TTilesetTab(container);
#ifdef GUI_STAND_ALONE
    for(int i=0;i<10;i++)
    {
        mTilesetTab->addTab(new QStringListModel(this), QString::number(i+1));
    }
#endif
    QToolBar *toolBar = new QToolBar(container);
    toolBar->setFloatable(false);//否定工具栏作为独立窗口
    toolBar->setMovable(false);//工具栏控件在工具栏中拖动
    toolBar->setIconSize(QSize(16, 16));
    toolBar->addAction(mActionAddTileset);
    toolBar->addAction(mActionRemoveTileset);

    QVBoxLayout *vboxLayout = new QVBoxLayout;//垂直
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
    case QEvent::LanguageChange://语言变化
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
