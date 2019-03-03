#ifndef SOUNDSETCONTROLLER_H
#define SOUNDSETCONTROLLER_H

#include "abstractcontroller.h"
#include "propertycontroller.h"

class TSoundSet;
class TSoundItem;
class TSoundSetView;
class TSoundResourceDialog;
typedef QList<TSoundItem *> TSoundItemList;

class TSoundSetController : public TAbstractController
{
    Q_OBJECT

public:
    TSoundSetController(QObject *parent = 0);
    ~TSoundSetController();

    bool joint(TMainWindow *mainWindow, TCore *core) Q_DECL_OVERRIDE;
    void setCurrentDocument(TDocument *document) Q_DECL_OVERRIDE;

    TSoundSet *soundSet() const;
    void setSoundSet(TSoundSet *soundSet);

signals:

private slots:
    void slotRequestAddSoundItems();
    void slotRequestRemoveSoundItems(const QList<int> &indexList);
    void slotRowSelected(int index);
    void slotPropertyItemValueChanged(TPropertyItem *propertyItem, const QVariant &newValue);
    void slotSoundItemsAdded(const TSoundItemList &soundItemList, const QList<int> indexList);
    void slotSoundItemsRemoved(const TSoundItemList &soundItemList, const QList<int> indexList);

private:
    TSoundSet *mSoundSet;
    TSoundSetView *mSoundSetView;
    TPropertyController *mPropertyController;
    TSoundResourceDialog *mSoundResourceDialog;

protected slots:
    void slotTimerEvent() Q_DECL_OVERRIDE;
};

#endif // SOUNDSETCONTROLLER_H
