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
    setObjectName(QStringLiteral("AnimationsContainer"));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(1);
    verticalLayout->setMargin(3);
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(0);

    QToolBar *toolbar = new QToolBar(this);
    CREATE_ACTION(mBtnNewAnimation,":/toolbar/images/new.png",slotNewAnimationTriggered);
    CREATE_ACTION(mBtnCopyAnimation,":/toolbar/images/copy.png",slotCopyAnimationTriggered);
    CREATE_ACTION(mBtnRemoveAnimation,":/animationdock/images/remove.png",slotRemoveAnimationTriggered);
    CREATE_ACTION(mBtnPlay,":/animationdock/images/play.png",slotPlayTriggered);
    CREATE_ACTION(mBtnStop,":/animationdock/images/stop_play.png",slotStopTriggered);
    toolbar->addSeparator();
    CREATE_ACTION(mBtnAddFrame,":/framelistview/images/newimage.png",slotAddFrameTriggered);
    CREATE_ACTION(mBtnRemoveFrame,":/framelistview/images/removeimage.png",slotRemoveFrameTriggered);
    CREATE_ACTION(mBtnMoveUp,":/framelistview/images/up.png",slotMoveUpTriggered);
    CREATE_ACTION(mBtnMoveDown,":/framelistview/images/down.png",slotMoveDownTriggered);
    CREATE_ACTION(mBtnMoveLeft,":/framelistview/images/left.png",slotMoveLeftTriggered);
    CREATE_ACTION(mBtnMoveRight,":/framelistview/images/right.png",slotMoveRightTriggered);
    horizontalLayout->addWidget(toolbar);

    mSbFps = new QSpinBox(this);
    mSbFps->setMinimumSize(QSize(40, 24));
    mSbFps->setMaximumSize(QSize(40, 24));
    mSbFps->setMinimum(1);
    mSbFps->setMaximum(120);
    mSbFps->setValue(60);
    connect(mSbFps, SIGNAL(valueChanged(int)), this, SIGNAL(requestAdjustFPS(int)));
    horizontalLayout->addWidget(mSbFps);

    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer);
    verticalLayout->addLayout(horizontalLayout);

    mAnimationListView = new TAnimationListView(this);
    mAnimationView = new TFrameListView(this);

    QSplitter *verticalSplitter = new QSplitter(this);
    verticalSplitter->setOrientation(Qt::Vertical);
    verticalSplitter->setOpaqueResize(true);
    verticalSplitter->setHandleWidth(2);
    verticalSplitter->setChildrenCollapsible(true);
    verticalSplitter->addWidget(mAnimationView);
    verticalSplitter->setStretchFactor(0, 5);
    verticalSplitter->setStretchFactor(1, 5);

    QSplitter *horrizontalSplitter = new QSplitter(this);
    horrizontalSplitter->setOrientation(Qt::Horizontal);
    horrizontalSplitter->setOpaqueResize(true);
    horrizontalSplitter->setHandleWidth(2);
    horrizontalSplitter->setChildrenCollapsible(true);
    horrizontalSplitter->addWidget(mAnimationListView);
    horrizontalSplitter->addWidget(verticalSplitter);
    horrizontalSplitter->setStretchFactor(0, 2);
    horrizontalSplitter->setStretchFactor(1, 8);

    verticalLayout->addWidget(horrizontalSplitter);
    verticalLayout->setStretch(0, 1);
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

}

void TContainer::slotAddFrameTriggered()
{
    QStringList fileList;
    emit getSelectedImages(fileList);
    if(fileList.size() > 0)
        emit requestAddFrames(fileList, -1);
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

}

void TContainer::slotMoveDownTriggered()
{

}

void TContainer::slotMoveLeftTriggered()
{

}

void TContainer::slotMoveRightTriggered()
{

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
