#ifndef DOCUMENT_FRAME_H
#define DOCUMENT_FRAME_H

#include <QList>
#include <QByteArray>
#include <QGraphicsScene>

#include "../../../../base/pixmap.h"
#include "../../../../model/sound/soundset.h"
#include "area.h"
#include "hand.h"
#include "vector/vectortablemodel.h"

class TDocObject;
class TFrameScene;

namespace Model {
    class TFrame;
}
class TFrame : public TDocObject
{
    Q_OBJECT

public:
    TFrame(QObject *parent=nullptr);
    ~TFrame();

    static QString mimeType();

    TFrame *prevBuddy();
    void setPrevBuddy(TFrame *prevBuddy);

    QByteArray toByteArray() const;
    void loadFromByteArray(QByteArray *byteArray);
    void loadFromModel(const Model::TFrame &keyFrame, void *context=nullptr);
    Model::TFrame *toModel() const;

    TPixmap *pixmap() const;
    void setPixmap(TPixmap *pixmap);
    QString getImageName() const;
    void setImageName(const QString &imageName);

    TPropertySheet *propertySheet() const;

    TFrameScene *scene() const;

    QPointF vector() const;
    void setVector(const QPointF &vector);

    bool antiGravity() const;
    void setAntiGravity(bool antiGravity);

    int duration() const;
    void setDuration(int duration);

    QPointF anchor() const;
    void setAnchor(const QPointF &anchor);
    void cmdSetAnchor(const QPointF &anchor);

    bool hasCollideArea() const;
    bool hasAttackArea() const;
    bool hasUndertakeArea() const;
    bool hasTerrianArea() const;
    bool hasSound() const;
    bool hasVector() const;

    void addCollideArea(const QRectF &rect);
    void addAttackArea(const QRectF &rect);
    void addUndertakeArea(const QRectF &rect);
    void addTerrianArea(const QRectF &rect);

    TAreaManager *collideAreaManager() const;
    TAreaManager *attackAreaManager() const;
    TAreaManager *undertakeAreaManager() const;
    TAreaManager *terrianAreaManager() const;

    void cmdAddCollideArea(const QRectF &rect);
    void cmdAddAttackArea(const QRectF &rect);
    void cmdAddUndertakeArea(const QRectF &rect);
    void cmdaddTerrianArea(const QRectF &rect);
    void cmdAddArea(const QRectF &rect, TArea::Type type);
    void cmdRemoveAreas(const QList<TArea*> &areaList);
    void cmdMoveAreas(const QList<TArea*> &areaList, const QPointF &distance);

    static TFrame *standardFrame();
    static void setStandardFrame(TFrame *standardFrame);

    void moveAnchor(const QPointF &distance);

    TSoundSet *soundSet() const;
    TVectorTableModel *vectorTableModel() const;

    InterruptType getInterruptType() const;
    void setInterruptType(const InterruptType &interruptType);

signals:
    void propertyChanged(TPropertyItem *item, const QVariant &oldValue);

    // Send to frame list view
    void frameChanged();

    // Send to frame scene
    void frameBuddyChanged(TFrame *oldBuddy);

private slots:
    void slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue);
    void slotSoundItemsCountChanged(int oldCount, int newCount);
    void slotVectorItemsAdded(const TVectorItemList &vectorItemList, const QList<int> indexList);
    void slotVectorItemsRemoved(const TVectorItemList &vectorItemList, const QList<int> indexList);
    void slotVectorItemsCountChanged(int oldCount, int newCount);

private:
    QList<THand*> mHandList;
    QRectF mFootRect;
    TPixmap *mPixmap;

    TFrameScene *mScene;
    TDocument *mDocument;
    TAreaManager *mAreaManagers[TArea::TypeCount];
    TFrame *mPrevBuddy;
    TSoundSet *mSoundSet;
    TVectorTableModel *mVectorTableModel;
    static TFrame *mStandardFrame;

    void createScene();
    void initPropertySheet();

    void cmdAddCollideAreas(const TAreaList &areaList);
    void cmdAddAttackAreas(const TAreaList &areaList);
    void cmdAddUndertakeAreas(const TAreaList &areaList);
    void cmdaddTerrianAreas(const TAreaList &areaList);
    bool checkAreaList(const TAreaList &areaList);
};
typedef QList<TFrame*> TFramesList;

QDataStream &operator<<(QDataStream& out, const TFrame& frame);
QDataStream &operator>>(QDataStream& in, TFrame& frame);

#endif // DOCUMENT_FRAME_H
