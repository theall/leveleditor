#ifndef MOVEDOCK_H
#define MOVEDOCK_H

#include <QAction>
#include <QToolBar>

#include "../basedock.h"
#include "../propertydock/propertybrowser.h"

class TMoveDock : public TBaseDock
{
    Q_OBJECT

public:
    TMoveDock(QWidget *parent = nullptr);
    ~TMoveDock();

    TPropertyBrowser *propertyBrowser() const;

signals:
    void requestAddSoundItems();
    void requestRemoveSoundItems(const QList<int> &indexList);

private slots:
    void slotActionNewSoundItemTriggered();
    void slotActionRemoveSoundItemTriggered();
    void slotSoundModelValidChanged(bool valid);
    void slotSoundItemSelectionChanged(bool hasSelection);

private:
    QAction *mActionNewSoundItem;
    QAction *mActionRemoveSoundItem;

    TPropertyBrowser *mPropertyBrowser;

    // TBaseDock interface
public:
    void retranslateUi() Q_DECL_OVERRIDE;
};

#endif // MOVEDOCK_H
