#include "characterdock.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStackedWidget>

TCharacterDock::TCharacterDock(QWidget *parent) :
    TBaseDock(QLatin1String("CharacterDock"), parent)
  , mCharacterView(new TCharacterView(this))
  , mItemView(new TCharacterView(this))
  , mShotView(new TCharacterView(this))
  , mChunkView(new TCharacterView(this))
  , mStackedWidget(new QStackedWidget(this))
  , mActionGroup(new QActionGroup(this))
{
    QToolBar *toolBar = new QToolBar(this);//工具栏
    toolBar->setFloatable(false);//设置为不可浮动
    toolBar->setMovable(false);//设置为不可移动
    toolBar->setIconSize(QSize(16, 16));//设置图片

    QStringList pngFileList;
    pngFileList.append(":/animationdock/images/character.png");
    pngFileList.append(":/animationdock/images/item.png");
    pngFileList.append(":/animationdock/images/shot.png");
    pngFileList.append(":/animationdock/images/chunk.png");

    setEnabled(false);
    for(int i=0;i<PA_TOTAL_COUNT;i++) {
        QAction *action = toolBar->addAction(QIcon(pngFileList.at(i)), QString(), this, SLOT(slotActionToggled()));
        action->setData(i);
        action->setCheckable(true);
        mActionGroup->addAction(action);
    }

    mActionGroup->actions().at(0)->setChecked(true);

    QScrollArea *container = new QScrollArea(this);//提供了一个可以滚动的视口和两个滚动条
    container->setWidgetResizable(true);//设置窗口大小可以随意改变

    addCharacterView(mCharacterView);
    addCharacterView(mItemView);
    addCharacterView(mShotView);
    addCharacterView(mChunkView);

    QVBoxLayout *scrollAreaLayout = new QVBoxLayout(container);//垂直布局 用父级构造一个新的顶级垂直框。
    scrollAreaLayout->setContentsMargins(0, 0, 0, 0);//设置上下左右边距
    scrollAreaLayout->setSpacing(0);//设置控件之间的边距
    scrollAreaLayout->addWidget(toolBar);//将工具栏添加到窗口
    scrollAreaLayout->addWidget(mStackedWidget);//将列表窗口添加到窗口
    setWidget(container);//设置当前窗口为带有滚动条的窗口

    retranslateUi();

#ifdef GUI_STAND_ALONE
    for(int i=0;i<45;i++) {
        mCharacterView->add(QPixmap());
    }
#endif
}

TCharacterDock::~TCharacterDock()
{

}

PanelType TCharacterDock::getCurrentPanelType() const
{
    return (PanelType)mStackedWidget->currentIndex();
}

void TCharacterDock::slotActionToggled()
{
    QAction *action = (QAction*)sender();
    mStackedWidget->setCurrentIndex(action->data().toInt());
}

void TCharacterDock::slotButtonPushed(int index)
{
    emit buttonPushed((PanelType)mStackedWidget->currentIndex(), index);
}

void TCharacterDock::addCharacterView(TCharacterView *view)
{
    mStackedWidget->addWidget(view);
    connect(view, SIGNAL(buttonPushed(int)), this, SLOT(slotButtonPushed(int)));
}

void TCharacterDock::setPixmapSet(const PanelType &panelType, const QList<QPixmap> &pixmapSet, const QList<int> &idList)
{
    TCharacterView *characterView = nullptr;
    switch (panelType) {
    case PA_CHARACTER:
        characterView = mCharacterView;
        break;
    case PA_ITEM:
        characterView = mItemView;
        break;
    case PA_SHOT:
        characterView = mShotView;
        break;
    case PA_CHUNK:
        characterView = mChunkView;
        break;
    default:
        break;
    }
    if(characterView) {
        characterView->setPixmapSet(pixmapSet, idList);
    }
}

void TCharacterDock::selectIndex(const PanelType &panel, int index)
{
    mStackedWidget->setCurrentIndex(panel);

    TCharacterView *characterView = nullptr;
    switch (panel) {
    case PA_CHARACTER:
        characterView = mCharacterView;
        break;
    case PA_ITEM:
        characterView = mItemView;
        break;
    case PA_SHOT:
        characterView = mShotView;
        break;
    case PA_CHUNK:
        characterView = mChunkView;
        break;
    default:
        break;
    }
    if(characterView) {
        characterView->pushButton(index);
    }
}

TCharacterView *TCharacterDock::chunkView() const
{
    return mChunkView;
}

TCharacterView *TCharacterDock::shotView() const
{
    return mShotView;
}

TCharacterView *TCharacterDock::itemView() const
{
    return mItemView;
}

TCharacterView *TCharacterDock::characterView() const
{
    return mCharacterView;
}

void TCharacterDock::retranslateUi()
{
    setWindowTitle(tr("Character"));
}
