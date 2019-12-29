#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <QGraphicsScene>

#include "tabcontainer.h"

class TTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    TTabWidget(QWidget *parent = nullptr);
    ~TTabWidget();

    int addTab(void *document, const QString &name, const QPixmap &icon=QPixmap());
    int findDocumentIndex(void *document);
    bool removeTab(void *document);
    void *currentDocument();
    void setDocumentDirty(void *document, bool isDirty);
    TTabContainer *currentContainer() const;
    TGraphicsView *currentGraphicsView() const;
    QGraphicsScene *currentGraphicsScene() const;
    void setGraphicsScene(int index, QGraphicsScene *scene);

    void setDocumentIcon(void *document, const QIcon &icon);
    void moveTab(int from, int to);
    void indexChange();

signals:
    // To TTabController
    void requestSwitchToDocument(void *document);
    void requestCloseDocument(void *document);
    void requestExploreFile(const QString &file);
    void requestStartMove(void *document);
    void requestStopMove(void *document);

    // To main window
    void onTabCountChanged(int count);
    void onActionSaveTriggered();
    void onMouseMoved(const QPoint &pos);

private slots:
    void slotOnCurrentIndexChanged(int index);
    void slotRequestCloseTab(int index);
    void slotOnTabMoved(int from, int to);
    void slotRequestStopMove();
    void slotRequestStartMove();
    void slotSwitchToLeft();
    void slotSwitchToRight();
    void slotCustomContextMenuRequested(const QPoint &pos);
    void slotActionCloseTriggered();
    void slotActionCloseLeftTriggered();
    void slotActionCloseRightTriggered();
    void slotActionCloseOtherTriggered();
    void slotActionSaveTriggered();
    void slotActionExploreTriggered();

    void slotActionStartMoveTriggered(int index);
    void slotActionStopMoveTriggered(int index);

private:
    QList<void*> mDocuments;//函数列表
    QMenu *mContextMenu;  //QMenu 设置菜单图标 生成菜单树 类如左上角文件
    QAction *mActionClose;
    QAction *mActionCloseLeft;
    QAction *mActionCloseRight;
    QAction *mActionCloseOther;
    QAction *mActionSave;
    QAction *mActionExplore;
    QAction *mActionStartMove;
    QAction *mActionStopMove;

    void switchTo(int diff);
    void setTabDirty(int index, bool isDirty);
    void retranslateUi();
};

#endif // TABWIDGET_H
