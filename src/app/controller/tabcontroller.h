#ifndef TABCONTROLLER_H
#define TABCONTROLLER_H

#include "abstractcontroller.h"

class TGraphicsScene;
class TTabWidget;
class TGraphicsViewContextMenu;

class TTabController : public TAbstractController
{
    Q_OBJECT

public:
    TTabController(QObject *parent = 0);
    ~TTabController();

    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;
    void removeDocument(TDocument *document);
    TDocument *currentDocument();
    TGraphicsScene *currentGraphicsScene() const;
    int addDocument(TDocument *document);

public slots:
    // From main controler
    void setGraphicsScene(int index, TGraphicsScene *scene);
    void play();
    void stop();

signals:
    // Send to main controller
    void requestSwitchToDocument(TDocument *document);
    void requestCloseDocument(TDocument *document);
    void documentDirtyFlagChanged(TDocument *document, bool isDirty);

    void pressDownCopy();
    void pressDownPaste(const QPointF &pos);
    void pressDownDelete();

private:
    TTabWidget *mTabWidget;
    TGraphicsViewContextMenu *mGraphicsViewContextMenu;
    QList<TDocument*> mChangedDocuments;
    QDateTime mLastCheckTime;
    int mLastListCount;
    bool mLock;

private slots:
    // From TTabWidget
    void slotRequestSwithToDocument(void *document);
    void slotRequestCloseDocument(void *document);
    void slotRequestExploreFile(const QString &file);
    void slotRequestStartMove(void* document);
    void slotRequestStopMove(void* document);
    void slotRequestPopupContextMenu();
    void slotPressDownClone();

    // From TDocument
    void slotDocumentDirtyFlagChanged(bool isDirty);
    void slotDocumentIconChanged(TPixmap *newPixmap);

    // From TFileSystemWatcher
    void slotDocumentFileChanged(const QString &file);

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // TABCONTROLLER_H
