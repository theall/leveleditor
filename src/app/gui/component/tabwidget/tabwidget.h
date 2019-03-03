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
    TTabContainer *currentContainer();
    TGraphicsView *currentGraphicsView();

    void setDocumentIcon(void *document, const QIcon &icon);
    void moveTab(int from, int to);
signals:
    // To TTabController
    void requestSwitchToDocument(void *document);
    void requestCloseDocument(void *document);

    // To main window
    void onTabCountChanged(int count);
    void onActionSaveTriggered();

private slots:
    void slotOnCurrentIndexChanged(int index);
    void slotRequestCloseTab(int index);
    void slotOnTabMoved(int from, int to);
    void slotSwitchToLeft();
    void slotSwitchToRight();
    void slotCustomContextMenuRequested(const QPoint &pos);
    void slotActionCloseTriggered();
    void slotActionCloseLeftTriggered();
    void slotActionCloseRightTriggered();
    void slotActionCloseOtherTriggered();
    void slotActionSaveTriggered();
    void slotActionExplorerTriggered();

private:
    QList<void*> mDocuments;
    QMenu *mContextMenu;
    QAction *mActionClose;
    QAction *mActionCloseLeft;
    QAction *mActionCloseRight;
    QAction *mActionCloseOther;
    QAction *mActionSave;
    QAction *mActionExplorer;

    void switchTo(int diff);
    void setTabDirty(int index, bool isDirty);
    void retranslateUi();
};

#endif // TABWIDGET_H
