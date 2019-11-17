#include "mapsdock.h"

#include <QSplitter>
#include <QVBoxLayout>

TMapsDock::TMapsDock(QWidget *parent) :
    TBaseDock(QLatin1String("MapsDock"), parent)
  , mMapsProxyView(new TMapsProxyView(this))
{
    CREATE_ACTION_TOGGLED(mActionShowTreeView, ":/mapsdock/images/tree.png", slotActionShowTreeViewToggled);
    QToolBar *toolBar = new QToolBar(this);
    toolBar->setFloatable(false);//是否能够独立拖放
    toolBar->setMovable(false);//是否能够在工具栏与工具栏之间移动
    toolBar->setIconSize(QSize(16, 16));
    toolBar->addAction(mActionShowTreeView);//将图标添加到工具栏

    QWidget *container = new QWidget(this);
    QSplitter *splitter = new QSplitter(this);//拆分器
    splitter->setOrientation(Qt::Vertical);//垂直
    splitter->addWidget(mMapsProxyView);
    QVBoxLayout *vBoxLayout = new QVBoxLayout;//垂直排列
    vBoxLayout->setContentsMargins(2, 2, 2, 2);//上下左右的边距
    vBoxLayout->setSpacing(0);//将“间距”属性设置为“间距”。
    vBoxLayout->addWidget(toolBar);
    vBoxLayout->addWidget(splitter);
    container->setLayout(vBoxLayout);
    setWidget(container);//显示

    mActionShowTreeView->setChecked(true);
    //此属性保留是否检查操作。只能检查可检查的操作。默认情况下，这是false（操作未选中）
    retranslateUi();
}

TMapsDock::~TMapsDock()
{

}

void TMapsDock::slotActionShowTreeViewToggled(bool checked)
{
    mMapsProxyView->setViewMode(checked?TMapsProxyView::Tree:TMapsProxyView::Tab);
}

TMapsProxyView *TMapsDock::mapsProxyView() const
{
    return mMapsProxyView;
}

void TMapsDock::retranslateUi()
{
    setWindowTitle(tr("Maps"));//标题名
    setToolTip(tr("Maps manager."));//此属性保存小部件的工具提示。

    if(mActionShowTreeView->isChecked()) {//检查操作
        mActionShowTreeView->setToolTip(tr("Toggle to show tab view."));
        mActionShowTreeView->setText(tr("Tab view"));
    } else {
        mActionShowTreeView->setToolTip(tr("Toggle to show tree view."));
        mActionShowTreeView->setText(tr("Tree view"));
    }
}
