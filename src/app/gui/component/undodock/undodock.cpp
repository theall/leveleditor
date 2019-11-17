#include "undodock.h"

#include <QEvent>
#include <QUndoView>
#include <QVBoxLayout>

TUndoDock::TUndoDock(QWidget *parent)
    : TBaseDock(QLatin1String("UndoViewDock"), parent)
{
    mUndoView = new QUndoView(this);
    mUndoView->setFrameShape(QFrame::Panel);
    mUndoView->setFrameShadow(QFrame::Sunken);
    QIcon cleanIcon(QLatin1String(":/undodock/images/empty.png"));
    mUndoView->setCleanIcon(cleanIcon);
    //此属性保存用于表示清除状态的图标。
    mUndoView->setUniformItemSizes(true);
    //此属性保留listview中的所有项是否具有相同的大小。
    //只有在确保视图中的所有项都具有相同的大小时，才应将此属性设置为true。这使视图能够为性能目的进行一些优化。
    //默认情况下，此属性为false。

    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setMargin(5);//此属性保留布局外部边框的宽度。
    layout->addWidget(mUndoView);

    setWidget(widget);
    retranslateUi();
}

TUndoDock::~TUndoDock()
{

}

void TUndoDock::setUndoGroup(QUndoGroup *undoGroup)
{
    if(mUndoView)
        mUndoView->setGroup(undoGroup);
}

void TUndoDock::retranslateUi()
{
    setWindowTitle(tr("History"));//设置窗口标题
    mUndoView->setEmptyLabel(tr("<empty>"));//它表示在将任何命令推送到堆栈上之前文档的状态。默认为字符串“<empty>”。
}
