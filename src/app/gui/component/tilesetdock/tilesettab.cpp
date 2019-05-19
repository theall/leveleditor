#include "tilesettab.h"
#include "tilesetview.h"

#include <QShortcut>
TTilesetTab::TTilesetTab(QWidget *parent) :
    QTabWidget(parent)
  , mContextMenu(new QMenu(this))
{
    setDocumentMode(true);
    setTabsClosable(false);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resize(240, 320);

    QTabBar *bar = tabBar();
    bar->setMovable(false);
    bar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(bar, SIGNAL(currentChanged(int)), this, SLOT(slotOnCurrentIndexChanged(int)));
    connect(bar, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomContextMenuRequested(QPoint)));

    QShortcut *switchToLeftTileset = new QShortcut(tr("Alt+Left"), this);
    QShortcut *switchToLeftTileset1 = new QShortcut(tr("Ctrl+Shift+Tab"), this);
    connect(switchToLeftTileset, SIGNAL(activated()), this, SLOT(slotSwitchToLeft()));
    connect(switchToLeftTileset1, SIGNAL(activated()), this, SLOT(slotSwitchToLeft()));

    QShortcut *switchToRightTileset = new QShortcut(tr("Alt+Right"), this);
    QShortcut *switchToRightTileset1 = new QShortcut(tr("Ctrl+Tab"), this);
    connect(switchToRightTileset, SIGNAL(activated()), this, SLOT(slotSwitchToRight()));
    connect(switchToRightTileset1, SIGNAL(activated()), this, SLOT(slotSwitchToRight()));

    mActionAddTiles = mContextMenu->addAction(QString(), this, SLOT(slotActionAddTilesTriggered()));
    mContextMenu->addSeparator();
    mActionAddTileset = mContextMenu->addAction(QString(), this, SLOT(slotActionRemoveTilesTriggered()));

    retranslateUi();
}

TTilesetTab::~TTilesetTab()
{

}

int TTilesetTab::addTab(QAbstractItemModel *tilesetModel, const QString &name, const QPixmap &icon)
{
    mTilesets.append(tilesetModel);

    TTilesetView *view = new TTilesetView(this);
    connect(view, SIGNAL(currentRowChanged(int)), this, SLOT(slotOnTilesetRowChanged(int)));

    view->setModel(tilesetModel);
    int i =  QTabWidget::addTab(view, QIcon(icon), name);
    emit onTabCountChanged(count());
    return i;
}

int TTilesetTab::findTilesetIndex(void *tileSet)
{
    for(int i=0;i<mTilesets.size();i++)
    {
        if(mTilesets[i]==tileSet)
            return i;
    }
    return -1;
}

bool TTilesetTab::removeTab(void *tileSet)
{
    int index = findTilesetIndex(tileSet);
    if(index != -1)
    {
        TTilesetView *view = (TTilesetView*)mTilesets.takeAt(index);
        if(view) {
            view->disconnect(this);
            QTabWidget::removeTab(index);
            emit onTabCountChanged(count());
            return true;
        }
    }
    return false;
}

void *TTilesetTab::currentTileset()
{
    void *tileSet = mTilesets.at(currentIndex());
    Q_ASSERT(tileSet);

    return tileSet;
}

void TTilesetTab::setTilesetIcon(void *tileSet, const QIcon &icon)
{
    int index = findTilesetIndex(tileSet);
    if(index == -1)
        return;

    setTabIcon(index, icon);
}

void TTilesetTab::selectIndex(int tabIndex, int tileIndex)
{
    TTilesetView *view = (TTilesetView*)widget(tabIndex);
    if(view) {
        setCurrentIndex(tabIndex);
        view->selectRow(tileIndex);
    }
}

void TTilesetTab::slotOnCurrentIndexChanged(int index)
{
    void *tileSet = nullptr;
    if(index>-1 && index < mTilesets.size())
    {
        tileSet = mTilesets.at(index);
        Q_ASSERT(tileSet);
    }
    emit requestSwitchToTileset(tileSet);
}

void TTilesetTab::slotSwitchToLeft()
{
    switchTo(-1);
}

void TTilesetTab::slotSwitchToRight()
{
    switchTo(1);
}

void TTilesetTab::slotCustomContextMenuRequested(const QPoint &pos)
{
    mContextMenu->popup(tabBar()->mapToGlobal(pos));
}

void TTilesetTab::slotActionAddTilesTriggered()
{

}

void TTilesetTab::slotActionRemoveTilesTriggered()
{

}

void TTilesetTab::slotOnTilesetRowChanged(int row)
{
    emit onTilesetViewRowChanged(currentIndex(), row);
}

void TTilesetTab::switchTo(int diff)
{
    int tabCount = count();
    int i = currentIndex() + diff;
    if(i < 0)
        i = 0;
    if(i >= tabCount)
        i = tabCount - 1;

    if(i>=0 && i < tabCount)
    {
        setCurrentIndex(i);
    }
}

void TTilesetTab::retranslateUi()
{
    mActionAddTiles->setText(tr("Add tiles"));
    mActionAddTileset->setText(tr("Add tileset"));
}
