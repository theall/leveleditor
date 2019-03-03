#ifndef UNDOCONTROLLER_H
#define UNDOCONTROLLER_H

#include "abstractcontroller.h"

#include <QUndoGroup>

class TUndoController : public TAbstractController
{
    Q_OBJECT

public:
    TUndoController(QObject *parent = 0);
    ~TUndoController();

    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

private slots:
    // From QUndoGroup
    void slotCanUndoChanged(bool canUndo);
    void slotCanRedoChanged(bool canRedo);

    // From mainwindow
    void slotRequestUndo();
    void slotRequestRedo();

private:
    QUndoGroup *mUndoGroup;

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // UNDOCONTROLLER_H
