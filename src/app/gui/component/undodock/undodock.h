#ifndef UNDODOCK_H
#define UNDODOCK_H

#include <QUndoGroup>
#include <QUndoView>

#include "../basedock.h"

/**
 * A dock widget showing the undo stack. Mainly for debugging, but can also be
 * useful for the user.
 */
class TUndoDock : public TBaseDock
{
    Q_OBJECT

public:
    TUndoDock(QWidget *parent = nullptr);
    ~TUndoDock();

    void setUndoGroup(QUndoGroup *undoGroup);

protected:

private:
    void retranslateUi();
    QUndoView *mUndoView;
};

#endif // UNDODOCK_H
