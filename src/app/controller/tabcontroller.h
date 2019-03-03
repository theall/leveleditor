#ifndef TABCONTROLLER_H
#define TABCONTROLLER_H

#include "abstractcontroller.h"

class TGraphicsScene;
class TTabWidget;

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

public slots:
    // From main controler
    void setGraphicsScene(TGraphicsScene *scene);
    void play();
    void stop();

signals:
    // Send to main controller
    void requestSwitchToDocument(TDocument *document);
    void requestCloseDocument(TDocument *document);
    void documentDirtyFlagChanged(TDocument *document, bool isDirty);

private:
    TTabWidget *mTabWidget;
    QList<TDocument*> mChangedDocuments;
    QDateTime mLastCheckTime;
    int mLastListCount;
    bool mLock;

    int addDocument(TDocument *document);

private slots:
    // From TTabWidget
    void slotRequestSwithToDocument(void *document);
    void slotRequestCloseDocument(void *document);

    // From TDocument
    void slotDocumentDirtyFlagChanged(bool isDirty);
    void slotDocumentIconChanged(TPixmap *newPixmap);

    // From TFileSystemWatcher
    void slotDocumentFileChanged(const QString &file);

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // TABCONTROLLER_H
