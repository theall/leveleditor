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

    QShortcut *switchToLeftTileSet = new QShortcut(tr("Alt+Left"), this);
    QShortcut *switchToLeftTileSet1 = new QShortcut(tr("Ctrl+Shift+Tab"), this);
    connect(switchToLeftTileSet, SIGNAL(activated()), this, SLOT(slotSwitchToLeft()));
    connect(switchToLeftTileSet1, SIGNAL(activated()), this, SLOT(slotSwitchToLeft()));

    QShortcut *switchToRightTileSet = new QShortcut(tr("Alt+Right"), this);
    QShortcut *switchToRightTileSet1 = new QShortcut(tr("Ctrl+Tab"), this);
    connect(switchToRightTileSet, SIGNAL(activated()), this, SLOT(slotSwitchToRight()));
    connect(switchToRightTileSet1, SIGNAL(activated()), this, SLOT(slotSwitchToRight()));

    mActionAddTiles = mContextMenu->addAction(QString(), this, SLOT(slotActionAddTilesTriggered()));
    mContextMenu->addSeparator();
    mActionAddTileSet = mContextMenu->addAction(QString(), this, SLOT(slotActionRemoveTilesTriggered()));

    retranslateUi();
}

TTilesetTab::~TTilesetTab()
{

}

int TTilesetTab::addTab(void *tileSet, const QString &name, const QPixmap &icon)
{
    mTileSets.append(tileSet);

    TTileSetView *view = new TTileSetView(this);
    int i =  QTabWidget::addTab(view, QIcon(icon), name);
    emit onTabCountChanged(count());
    return i;
}

int TTilesetTab::findTileSetIndex(void *tileSet)
{
    for(int i=0;i<mTileSets.size();i++)
    {
        if(mTileSets[i]==tileSet)
            return i;
    }
    return -1;
}

bool TTilesetTab::removeTab(void *tileSet)
{
    int index = findTileSetIndex(tileSet);
    if(index != -1)
    {
        mTileSets.takeAt(index);
        QTabWidget::removeTab(index);
        emit onTabCountChanged(count());
        return true;
    }
    return false;
}

void *TTilesetTab::currentTileSet()
{
    void *tileSet = mTileSets.at(currentIndex());
    Q_ASSERT(tileSet);

    return tileSet;
}

void TTilesetTab::setTileSetIcon(void *tileSet, const QIcon &icon)
{
    int index = findTileSetIndex(tileSet);
    if(index == -1)
        return;

    setTabIcon(index, icon);
}

void TTilesetTab::slotOnCurrentIndexChanged(int index)
{
    void *tileSet = nullptr;
    if(index>-1 && index < mTileSets.size())
    {
        tileSet = mTileSets.at(index);
        Q_ASSERT(tileSet);
    }
    emit requestSwitchToTileSet(tileSet);
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
    mActionAddTileSet->setText(tr("Add tileset"));
}
