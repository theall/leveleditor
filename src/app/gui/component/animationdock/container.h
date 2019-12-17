#ifndef CONTAINER_H
#define CONTAINER_H

#include <QWidget>
#include <QSpinBox>
#include <QAction>
#include "animationlistview.h"
#include "framelistview.h"

enum Dir{
    Up,
    Down,
    Left,
    Right
};

class TContainer : public QWidget
{
    Q_OBJECT

public:
    explicit TContainer(QWidget *parent = 0);
    ~TContainer();

    TAnimationListView *getAnimationListView() const;
    TFrameListView *getFrameListView() const;

    void setFPS(int fps);

signals:
    // Controller
    void requestAddNewAnimation(const QString &name);
    void requestRemoveAnimations(const QList<int> &rows);
    void requestAddFrames(const QStringList &fileList, int pos);
    void requestRemoveFrames(const QList<int> &indexes);
    void requestCopyFrames(const QList<int> &indexes);
    void requestCloneFrames(const QList<int> &indexes);
    void requestMoveIndexs(const QList<int> &indexs, const Dir);
    void requestPasteFrames(int pos);
    void requestAddAnimation();
    void requestAddFrames();
    void requestPlayAnimation();
    void requestStopPlayAnimation();
    void requestAdjustFPS(int fps);
    void requestCreateAnimationTrigger();
    void requestRemoveAnimationTrigger(QList<int> rows);
    void requestModifyAnimationTrigger(int row);

    // Main window
    void getSelectedImages(QStringList &fileList);

private slots:
    void slotPlayTriggered();
    void slotCopyAnimationTriggered();
    void slotStopTriggered();
    void slotRemoveAnimationTriggered();
    void slotNewAnimationTriggered();
    void slotAddFrameTriggered();
    void slotRemoveFrameTriggered();
    void slotCopyFramesTriggered();
    void slotPasteFramesTriggered();
    void slotMoveUpTriggered();
    void slotMoveDownTriggered();
    void slotMoveLeftTriggered();
    void slotMoveRightTriggered();

private:
    QAction *mBtnNewAnimation;// 类提供了一个抽象的用户界面操作，可以插入到小部件中
    QAction *mBtnPlay;
    QAction *mBtnCopyAnimation;
    QAction *mBtnStop;
    QAction *mBtnRemoveAnimation;
    QAction *mBtnAddFrame;
    QAction *mBtnRemoveFrame;
    QAction *mBtnMoveUp;
    QAction *mBtnMoveDown;
    QAction *mBtnMoveLeft;
    QAction *mBtnMoveRight;
    QAction *mBtnNewTrigger;
    QAction *mBtnRemoveTrigger;

    QSpinBox *mSbFps;
    TAnimationListView *mAnimationListView;
    TFrameListView *mAnimationView;

    void retranslateUi();
};

#endif // CONTAINER_H
