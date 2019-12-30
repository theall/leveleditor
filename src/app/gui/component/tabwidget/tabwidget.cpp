#include "tabwidget.h"

#include <QTabBar>
#include <QShortcut>

#define DIRTY_SUFFIX '*'

TTabWidget::TTabWidget(QWidget *parent) ://构造函数里面传递了一个QWidget 类的指针 有Q开头的都是自带类
    QTabWidget(parent)//设置样式类 里面传递一个 指针
  , mContextMenu(new QMenu(this))//QMenu 设置菜单图标 生成菜单树 类如左上角文件
{
    setDocumentMode(true); //传递了一个1 这个函数是设置文档模式 里面包含读写
    //此属性保留是否以适合文档页的模式呈现选项卡小部件这与OS X上的文档模式相同。
    //设置此属性时，不会呈现选项卡小部件帧此模式对于显示文档类型的页面非常有用，页面覆盖了大部分选项卡小部件区域。
    setTabsClosable(true); //传递了一个1
    //此属性保留是否自动将关闭按钮添加到每个选项卡。  就是判断左上角选项是否自动添加
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);//Expanding此枚举描述构造QSizePolicy时使用的各种按维度大小调整类型。
    resize(640, 480);

    QTabBar *bar = tabBar();//那边返回了一个Qtabbar 的包
    bar->setMovable(true);//设置可以移动，为false不能动
    bar->setContextMenuPolicy(Qt::CustomContextMenu);//反键菜单
    connect(bar, SIGNAL(currentChanged(int)), this, SLOT(slotOnCurrentIndexChanged(int)));//切换窗口
    connect(bar, SIGNAL(tabCloseRequested(int)), this, SLOT(slotRequestCloseTab(int)));//按钮关闭
    connect(bar, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(slotRequestCloseTab(int)));//双击关闭
    connect(bar, SIGNAL(tabMoved(int,int)), this, SLOT(slotOnTabMoved(int,int)));//样式设置为索引顺序拖动
    connect(bar, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomContextMenuRequested(QPoint)));//鼠标坐标局部转全局
    //新建快捷键
    QShortcut *switchToLeftDocument = new QShortcut(tr("Alt+Left"), this);
    QShortcut *switchToLeftDocument1 = new QShortcut(tr("Ctrl+Shift+Tab"), this);
    connect(switchToLeftDocument, SIGNAL(activated()), this, SLOT(slotSwitchToLeft()));//左移一
    connect(switchToLeftDocument1, SIGNAL(activated()), this, SLOT(slotSwitchToLeft()));//左移一
    //新建快捷键
    QShortcut *switchToRightDocument = new QShortcut(tr("Alt+Right"), this);
    QShortcut *switchToRightDocument1 = new QShortcut(tr("Ctrl+Tab"), this);
    connect(switchToRightDocument, SIGNAL(activated()), this, SLOT(slotSwitchToRight()));//右移一
    connect(switchToRightDocument1, SIGNAL(activated()), this, SLOT(slotSwitchToRight()));//右移一

    mActionClose = mContextMenu->addAction(QString(), this, SLOT(slotActionCloseTriggered()));//关闭当前索引的文档
    mActionCloseOther = mContextMenu->addAction(QString(), this, SLOT(slotActionCloseOtherTriggered()));//翻译为其他的 作用与删除当前索引右边的所有文档一样
    mActionCloseLeft = mContextMenu->addAction(QString(), this, SLOT(slotActionCloseLeftTriggered()));//删除当前索引左边的所有文档
    mActionCloseRight = mContextMenu->addAction(QString(), this, SLOT(slotActionCloseRightTriggered()));//删除当前索引右边的所有文档
    mActionSave = mContextMenu->addAction(QString(), this, SIGNAL(onActionSaveTriggered()));//操作保存已触发

    mContextMenu->addSeparator();//添加新建的分割符
    mActionExplore = mContextMenu->addAction(QString(), this, SLOT(slotActionExploreTriggered()));//返回当前文档的位置
    mContextMenu->addSeparator();
    // mActionStartMove = mContextMenu->addAction(QString(),this,SLOT(slotRequestStartMove()));
    // mActionStopMove = mContextMenu->addAction(QString(),this,SLOT(slotRequestStopMove()));

    mActionCloseOther->setVisible(true);
    mActionCloseLeft->setVisible(true);
    mActionCloseRight->setVisible(true);

    retranslateUi();

}

TTabWidget::~TTabWidget()
{

}

int TTabWidget::addTab(void *document, const QString &name, const QPixmap &icon)
{
    //返回值在列表中第一次出现时的索引位置，从索引位置开始向前搜索。如果没有匹配的项，则返回-1。
    if(mDocuments.indexOf(document) != -1)
        return -1;

    mDocuments.append(document);//在列表末尾插入值。

    TTabContainer *view = new TTabContainer(this);
    int i =  QTabWidget::addTab(view, QIcon(icon), name);
    emit onTabCountChanged(count());
    connect(view->graphicsView(), SIGNAL(onMouseMoved(QPointF)), this, SIGNAL(onMouseMoved(QPointF)));
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
    emit requestSwitchToDocument(document);//发送切换文档信号
}

void TTabWidget::slotRequestCloseTab(int index)
{
    if(index>-1 && index < mDocuments.size())//判断该文档是否存在
    {
        void *document = mDocuments.at(index);
        Q_ASSERT(document);

        emit requestCloseDocument(document);//请求关闭文档
    }
}

void TTabWidget::slotOnTabMoved(int from, int to)
{
    void *d = mDocuments.takeAt(to);
    mDocuments.insert(from, d);
}

void TTabWidget::slotRequestStopMove()
{
    int index = currentIndex();
    if(index != -1)
        slotActionStopMoveTriggered(index);
}

void TTabWidget::slotSwitchToLeft()
{
    switchTo(-1);
}

void TTabWidget::slotSwitchToRight()
{
    switchTo(1);
}

void TTabWidget::slotRequestStartMove()
{
    int index = currentIndex();
    if(index != -1)
        slotActionStartMoveTriggered(index);
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
        slotRequestCloseTab(index);//关闭当前文档
}

void TTabWidget::slotActionCloseLeftTriggered()
{
    int index = currentIndex();
    if(index == -1)
        return;

    for(int i=0;i<index;i++)
    {
        slotRequestCloseTab(0);//删除当前索引之前的所有文档
    }
}

void TTabWidget::slotActionCloseRightTriggered()
{
    int index = currentIndex();
    if(index == -1)
        return;

    int j = count();
    for(int i=index+1;i<j;i++)
    {
        slotRequestCloseTab(index+1);
    }
}

void TTabWidget::slotActionCloseOtherTriggered()
{
    slotActionCloseLeftTriggered();
    slotActionCloseRightTriggered();
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

    //返回位于位置索引处的页的选项卡工具提示，如果未设置工具提示，则返回空字符串。
    QString fileName = tabToolTip(index);
    emit requestExploreFile(fileName);//请求探索文件
}

void TTabWidget::slotActionStartMoveTriggered(int index)
{
    if(index>-1 && index < mDocuments.size())
    {
        void *document = mDocuments.at(index);
        Q_ASSERT(document);

        emit requestStartMove(document);
    }
}

void TTabWidget::slotActionStopMoveTriggered(int index)
{
    if(index>-1 && index < mDocuments.size())
    {
        void *document = mDocuments.at(index);
        Q_ASSERT(document);

        emit requestStopMove(document);
    }
}



