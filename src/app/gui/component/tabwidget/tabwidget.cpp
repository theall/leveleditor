#include "tabwidget.h"

#include <QTabBar>
#include <QShortcut>

#define DIRTY_SUFFIX '*'

TTabWidget::TTabWidget(QWidget *parent) :
    QTabWidget(parent)
  , mContextMenu(new QMenu(this))
{
    setDocumentMode(true);
    setTabsClosable(true);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    resize(640, 480);

    QTabBar *bar = tabBar();
    bar->setMovable(true);
    bar->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(bar, SIGNAL(currentChanged(int)), this, SLOT(slotOnCurrentIndexChanged(int)));
    connect(bar, SIGNAL(tabCloseRequested(int)), this, SLOT(slotRequestCloseTab(int)));
    connect(bar, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(slotRequestCloseTab(int)));
    connect(bar, SIGNAL(tabMoved(int,int)), this, SLOT(slotOnTabMoved(int,int)));
    connect(bar, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomContextMenuRequested(QPoint)));

    QShortcut *switchToLeftDocument = new QShortcut(tr("Alt+Left"), this);
    QShortcut *switchToLeftDocument1 = new QShortcut(tr("Ctrl+Shift+Tab"), this);
    connect(switchToLeftDocument, SIGNAL(activated()), this, SLOT(slotSwitchToLeft()));
    connect(switchToLeftDocument1, SIGNAL(activated()), this, SLOT(slotSwitchToLeft()));

    QShortcut *switchToRightDocument = new QShortcut(tr("Alt+Right"), this);
    QShortcut *switchToRightDocument1 = new QShortcut(tr("Ctrl+Tab"), this);
    connect(switchToRightDocument, SIGNAL(activated()), this, SLOT(slotSwitchToRight()));
    connect(switchToRightDocument1, SIGNAL(activated()), this, SLOT(slotSwitchToRight()));

    mActionClose = mContextMenu->addAction(QString(), this, SLOT(slotActionCloseTriggered()));
    mActionCloseOther = mContextMenu->addAction(QString(), this, SLOT(slotActionCloseOtherTriggered()));
    mActionCloseLeft = mContextMenu->addAction(QString(), this, SLOT(slotActionCloseLeftTriggered()));
    mActionCloseRight = mContextMenu->addAction(QString(), this, SLOT(slotActionCloseRightTriggered()));
    mActionSave = mContextMenu->addAction(QString(), this, SIGNAL(onActionSaveTriggered()));
    mContextMenu->addSeparator();
    mActionExplore = mContextMenu->addAction(QString(), this, SLOT(slotActionExploreTriggered()));

    mActionCloseOther->setVisible(false);
    mActionCloseLeft->setVisible(false);
    mActionCloseRight->setVisible(false);

    retranslateUi();
}

TTabWidget::~TTabWidget()
{

}

int TTabWidget::addTab(void *document, const QString &name, const QPixmap &icon)
{
    if(mDocuments.indexOf(document) != -1)
        return -1;

    mDocuments.append(document);

    TTabContainer *view = new TTabContainer(this);
    int i =  QTabWidget::addTab(view, QIcon(icon), name);
    emit onTabCountChanged(count());
    return i;
}

int TTabWidget::findDocumentIndex(void *document)
{
    for(int i=0;i<mDocuments.size();i++)
    {
        if(mDocuments[i]==document)
            return i;
    }
    return -1;
}

bool TTabWidget::removeTab(void *document)
{
    int index = findDocumentIndex(document);
    if(index != -1)
    {
        mDocuments.takeAt(index);
        QTabWidget::removeTab(index);
        emit onTabCountChanged(count());
        return true;
    }
    return false;
}

void TTabWidget::moveTab(int from, int to)
{
    tabBar()->moveTab(from, to);
}

void *TTabWidget::currentDocument()
{
    void *document = mDocuments.at(currentIndex());
    Q_ASSERT(document);

    return document;
}

void TTabWidget::setDocumentDirty(void *document, bool isDirty)
{
    int index = findDocumentIndex(document);
    if(index == -1)
        return;

    setTabDirty(index, isDirty);
}

QGraphicsScene *TTabWidget::currentGraphicsScene() const
{
    TGraphicsView *view = currentGraphicsView();
    return view?view->scene():nullptr;
}

void TTabWidget::setGraphicsScene(int index, QGraphicsScene *scene)
{
    TTabContainer *tabContainer = static_cast<TTabContainer*>(widget(index));
    if(!tabContainer)
        return;

    tabContainer->setGraphicsScene(scene);
}

void TTabWidget::setDocumentIcon(void *document, const QIcon &icon)
{
    int index = findDocumentIndex(document);
    if(index == -1)
        return;

    setTabIcon(index, icon);
}

TTabContainer *TTabWidget::currentContainer() const
{
    return static_cast<TTabContainer*>(currentWidget());
}

TGraphicsView *TTabWidget::currentGraphicsView() const
{
    TTabContainer *tabContainer = static_cast<TTabContainer*>(currentWidget());
    return tabContainer?tabContainer->graphicsView():nullptr;
}

void TTabWidget::slotOnCurrentIndexChanged(int index)
{
    void *document = nullptr;
    if(index>-1 && index < mDocuments.size())
    {
        document = mDocuments.at(index);
        Q_ASSERT(document);
    }
    emit requestSwitchToDocument(document);
}

void TTabWidget::slotRequestCloseTab(int index)
{
    if(index>-1 && index < mDocuments.size())
    {
        void *document = mDocuments.at(index);
        Q_ASSERT(document);

        emit requestCloseDocument(document);
    }
}

void TTabWidget::slotOnTabMoved(int from, int to)
{
    void *d = mDocuments.takeAt(to);
    mDocuments.insert(from, d);
}

void TTabWidget::slotSwitchToLeft()
{
    switchTo(-1);
}

void TTabWidget::slotSwitchToRight()
{
    switchTo(1);
}

void TTabWidget::slotCustomContextMenuRequested(const QPoint &pos)
{
    mContextMenu->popup(tabBar()->mapToGlobal(pos));
}

void TTabWidget::switchTo(int diff)
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

void TTabWidget::setTabDirty(int index, bool isDirty)
{
    QString tabName = tabText(index);
    bool endWithAsterisk = tabName.endsWith(QChar(DIRTY_SUFFIX));
    if(isDirty)
    {
        if(!endWithAsterisk)
            tabName.append(QChar(DIRTY_SUFFIX));
    } else {
        if(endWithAsterisk)
            tabName.chop(1);
    }
    setTabText(index, tabName);
}

void TTabWidget::retranslateUi()
{
    mActionClose->setText(tr("Close"));
    mActionCloseLeft->setText(tr("Close All to the left"));
    mActionCloseRight->setText(tr("Close All to the right"));
    mActionCloseOther->setText(tr("Close All except this"));
    mActionSave->setText(tr("Save"));
    mActionExplore->setText(tr("Explore"));
}

void TTabWidget::slotActionCloseTriggered()
{
    int index = currentIndex();
    if(index != -1)
        slotRequestCloseTab(index);
}

void TTabWidget::slotActionCloseLeftTriggered()
{
    int index = currentIndex();
    if(index == -1)
        return;

    for(int i=0;i<index;i++)
    {
        slotRequestCloseTab(0);
    }
}

void TTabWidget::slotActionCloseRightTriggered()
{
    int index = currentIndex();
    if(index == -1)
        return;

    for(int i=index+1;i<count();i++)
    {
        slotRequestCloseTab(index+1);
    }
}

void TTabWidget::slotActionCloseOtherTriggered()
{
    int index = currentIndex();
    if(index == -1)
        return;

    for(int i=index+1;i<count();i++)
    {
        slotRequestCloseTab(index+1);
    }
}

void TTabWidget::slotActionSaveTriggered()
{
    emit onActionSaveTriggered();
}

void TTabWidget::slotActionExploreTriggered()
{
    int index = currentIndex();
    if(index == -1)
        return;

    QString fileName = tabToolTip(index);
    emit requestExploreFile(fileName);
}
