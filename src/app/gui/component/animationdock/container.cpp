#include "container.h"

#include <QToolBar>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>

#define CREATE_ACTION(action,image,func) \
    action = toolbar->addAction(QString());\
    action->setIcon(QIcon(image));\
    connect(action, SIGNAL(triggered()), this, SLOT(func()))

TContainer::TContainer(QWidget *parent) :
    QWidget(parent)
{
    setObjectName(QStringLiteral("AnimationsContainer"));//保存名字

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);//如果没有布局管理，则使用该函数的布局

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);//垂直布局
    verticalLayout->setSpacing(1);//将控件与控件之间的间距设为1
    verticalLayout->setMargin(3);//设置属性边缘
    QHBoxLayout *horizontalLayout = new QHBoxLayout();//水平布局
    horizontalLayout->setSpacing(0);//将控件与控件之间的间距设为1

    QToolBar *toolbar = new QToolBar(this);//工具栏
    CREATE_ACTION(mBtnNewAnimation,":/toolbar/images/new.png",slotNewAnimationTriggered);//文件  空
    CREATE_ACTION(mBtnCopyAnimation,":/toolbar/images/copy.png",slotCopyAnimationTriggered);//多个文件 空
    CREATE_ACTION(mBtnRemoveAnimation,":/animationdock/images/remove.png",slotRemoveAnimationTriggered);//减
    CREATE_ACTION(mBtnMoveUp,":/framelistview/images/up.png",slotMoveUpTriggered);//上
    CREATE_ACTION(mBtnMoveDown,":/framelistview/images/down.png",slotMoveDownTriggered);//下
    toolbar->addSeparator();//添加分隔符
    CREATE_ACTION(mBtnAddFrame,":/framelistview/images/newimage.png",slotAddFrameTriggered);//图片
    CREATE_ACTION(mBtnRemoveFrame,":/framelistview/images/removeimage.png",slotRemoveFrameTriggered);//X
    CREATE_ACTION(mBtnPlay,":/animationdock/images/play.png",slotPlayTriggered);//播放 发送信号
    CREATE_ACTION(mBtnStop,":/animationdock/images/stop_play.png",slotStopTriggered);//暂停 发送信号
    CREATE_ACTION(mBtnMoveLeft,":/framelistview/images/left.png",slotMoveLeftTriggered);//左
    CREATE_ACTION(mBtnMoveRight,":/framelistview/images/right.png",slotMoveRightTriggered);//右
    horizontalLayout->addWidget(toolbar);

    mBtnNewAnimation->setDisabled(true);

    mSbFps = new QSpinBox(this);//用于整数的输入和显示
    mSbFps->setMinimumSize(QSize(40, 24));//图片最小
    mSbFps->setMaximumSize(QSize(40, 24));//图片最大
    mSbFps->setMinimum(1);//最小值
    mSbFps->setMaximum(120);//最大值
    mSbFps->setValue(60);

    connect(mSbFps, SIGNAL(valueChanged(int)), this, SIGNAL(requestAdjustFPS(int)));
    horizontalLayout->addWidget(mSbFps);

    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);//给一个首选高度首选宽度 控件可以自行增大或者缩小 控件的sizeHint为控件的最小尺寸。控件不能小于这个sizeHint
    horizontalLayout->addItem(horizontalSpacer);
    verticalLayout->addLayout(horizontalLayout);//将水平布局添加到垂直布局中

    mAnimationListView = new TAnimationListView(this);
    mAnimationView = new TFrameListView(this);

    QSplitter *verticalSplitter = new QSplitter(this);//分离器
    verticalSplitter->setOrientation(Qt::Vertical);//保留拆分器的方向为垂直
    verticalSplitter->setOpaqueResize(true);//保留大小调整是否不透明
    verticalSplitter->setHandleWidth(2);//设置拆分器句柄的宽度
    verticalSplitter->setChildrenCollapsible(true);//保留用户是否可以将子小部件的大小调整为0
    verticalSplitter->addWidget(mAnimationView);//空白区
    verticalSplitter->setStretchFactor(0, 5);//设置控件0占5
    verticalSplitter->setStretchFactor(1, 5);//设置控件1占5

    QSplitter *horrizontalSplitter = new QSplitter(this);//分离器  工具区
    horrizontalSplitter->setOrientation(Qt::Horizontal);//水平
    horrizontalSplitter->setOpaqueResize(true);//设置不透明
    horrizontalSplitter->setHandleWidth(2);//设置分离器的句柄长度
    horrizontalSplitter->setChildrenCollapsible(true);
    horrizontalSplitter->addWidget(mAnimationListView);
    horrizontalSplitter->addWidget(verticalSplitter);
    horrizontalSplitter->setStretchFactor(0, 2);//设置控件0占2
    horrizontalSplitter->setStretchFactor(1, 8);//设置控件1占8

    verticalLayout->addWidget(horrizontalSplitter);
    verticalLayout->setStretch(0, 1);//设置索引位置的拉伸因子伸展
    verticalLayout->setStretch(1, 9);

    connect(mAnimationView, SIGNAL(requestRemoveFrames(QList<int>)), this, SIGNAL(requestRemoveFrames(QList<int>)));
    connect(mAnimationView, SIGNAL(requestCopyFrames(QList<int>)), this, SIGNAL(requestCopyFrames(QList<int>)));
    connect(mAnimationView, SIGNAL(requestCloneFrames(QList<int>)), this, SIGNAL(requestCloneFrames(QList<int>)));
    connect(mAnimationView, SIGNAL(requestPasteFrames(int)), this, SIGNAL(requestPasteFrames(int)));

    retranslateUi();
}

TContainer::~TContainer()
{

}

TAnimationListView *TContainer::getAnimationListView() const
{
    return mAnimationListView;
}

void TContainer::slotPlayTriggered()
{
    emit requestPlayAnimation();
}

void TContainer::slotCopyAnimationTriggered()
{

}

void TContainer::slotStopTriggered()
{
    emit requestStopPlayAnimation();
}

void TContainer::slotRemoveAnimationTriggered()
{
    QList<int> selectedRows = mAnimationListView->getSelectedIndexes();
    if(selectedRows.size() > 0) {
        emit requestRemoveAnimations(selectedRows);

        int currentRow = mAnimationListView->currentRow();
        int rowCount = mAnimationListView->rowCount();
        if(currentRow == -1)
            currentRow = 0;
        else if(currentRow >= rowCount)
            currentRow = rowCount - 1;
        mAnimationListView->selectRow(currentRow);
    }
}

void TContainer::slotNewAnimationTriggered()
{
        emit requestAddAnimation();
}

void TContainer::slotAddFrameTriggered()
{
    emit requestAddFrames();
//    QStringList fileList;
//    emit getSelectedImages(fileList);
//    if(fileList.size() > 0)
//        emit requestAddFrames(fileList, -1);
}

void TContainer::slotRemoveFrameTriggered()
{
    QList<int> selectedIndex = mAnimationView->getSelectedIndexes();
    if(selectedIndex.size() > 0)
        emit requestRemoveFrames(selectedIndex);
}

void TContainer::slotCopyFramesTriggered()
{
    QList<int> selectedIndex = mAnimationView->getSelectedIndexes();
    if(selectedIndex.size() > 0)
        emit requestCopyFrames(selectedIndex);
}

void TContainer::slotPasteFramesTriggered()
{

}

void TContainer::slotMoveUpTriggered()
{
    emit requestMoveIndexs(mAnimationListView->getSelectedIndexes(), Dir::Up);
}

void TContainer::slotMoveDownTriggered()
{
    emit requestMoveIndexs(mAnimationListView->getSelectedIndexes(), Dir::Down);
}

void TContainer::slotMoveLeftTriggered()
{
    emit requestMoveIndexs(mAnimationView->getSelectedIndexes(), Dir::Left);
}

void TContainer::slotMoveRightTriggered()
{
    emit requestMoveIndexs(mAnimationView->getSelectedIndexes(), Dir::Right);
}

void TContainer::setNewButtonAnimation(bool state)
{
    mBtnNewAnimation->setDisabled(state);
}

TFrameListView *TContainer::getFrameListView() const
{
    return mAnimationView;
}

void TContainer::setFPS(int fps)
{
    mSbFps->blockSignals(true);
    mSbFps->setValue(fps);
    mSbFps->blockSignals(false);
}

void TContainer::retranslateUi()
{

}
