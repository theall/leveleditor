#include "characterdock.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QScrollArea>

TCharacterDock::TCharacterDock(QWidget *parent) :
    TBaseDock(QLatin1String("CharacterDock"), parent)
  , mCharacterView(new TCharacterView(this))
{
    CREATE_ACTION_TOGGLED(mActionShowIcon, ":/animationdock/images/add.png", slotActionShowIconToggled);

    mActionShowIcon->setCheckable(true);

    QToolBar *toolBar = new QToolBar(this);//工具栏
    toolBar->setFloatable(false);//设置为不可浮动
    toolBar->setMovable(false);//设置为不可移动
    toolBar->setIconSize(QSize(16, 16));//设置图片
    toolBar->addAction(mActionShowIcon);//添加

    QScrollArea *container = new QScrollArea(this);//提供了一个可以滚动的视口和两个滚动条
    container->setWidgetResizable(true);//设置窗口大小可以随意改变

    QVBoxLayout *scrollAreaLayout = new QVBoxLayout(container);//垂直布局 用父级构造一个新的顶级垂直框。
    scrollAreaLayout->setContentsMargins(0, 0, 0, 0);//设置上下左右边距
    scrollAreaLayout->setSpacing(0);//设置控件之间的边距
    scrollAreaLayout->addWidget(toolBar);//将工具栏添加到窗口
    scrollAreaLayout->addWidget(mCharacterView);//将列表窗口添加到窗口
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

void TCharacterDock::slotActionShowIconToggled(bool toggled)
{
    if(toggled) {

    } else {

    }
}

TCharacterView *TCharacterDock::characterView() const
{
    return mCharacterView;
}

void TCharacterDock::retranslateUi()
{
    setWindowTitle(tr("Character"));
}
