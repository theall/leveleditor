#ifndef SOUNDDOCK_H
#define SOUNDDOCK_H

#include <QAction>
#include <QToolBar>

#include "soundsetview.h"
#include "../basedock.h"
#include "../propertydock/propertybrowser.h"

class TSoundDock : public TBaseDock
{
    Q_OBJECT

public:
    TSoundDock(QWidget *parent = nullptr);
    ~TSoundDock();

    TSoundSetView *soundSetView() const;
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

    TSoundSetView *mSoundSetView;
    TPropertyBrowser *mPropertyBrowser;

    // TBaseDock interface
public:
    void retranslateUi() Q_DECL_OVERRIDE;
};

#endif // SOUNDDOCK_H
