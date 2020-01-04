#ifndef TENEMY_H
#define TENEMY_H

#include <QList>

#include "pointobject.h"
#include "../../../assets/assetsmanager.h"

class TEnemy : public TPointObject
{
    Q_OBJECT

public:
    explicit TEnemy(QObject *parent = nullptr);

    TPixmap *getPixmap() const;
    TPixmapId *pixmapId() const;
    void setPixmapId(TPixmapId *pixmapId);

    QRectF getRect() const;

private:
    TPixmapId *mPixmapId;
    TPropertyItem *mCategoryPropertyItem;
    TPropertyItem *mEnemyPropertyItem;

    void initPropertySheet();
    void setUpPixmapId();

private slots:
    void slotCategoryChanged(const QVariant &oldValue, const QVariant &newValue);

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

    // TObject interface
public:
    QByteArray toByteArray(TObject *object) const;
    void loadFromByteArray(const QByteArray &byteArray);
};

typedef QList<TEnemy*> TEnemyList;

#endif // TENEMY_H
