#ifndef TENEMY_H
#define TENEMY_H

#include <QList>

#include "object.h"
#include "../../base/io.h"
#include "../../../assets/assetsmanager.h"

class TEnemy : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TEnemy(QObject *parent = nullptr);

    TPixmap *getPixmap() const;
    TPixmapId *pixmapId() const;
    void setPixmapId(TPixmapId *pixmapId);

    QPointF pos() const;
    void move(const QPointF &offset) Q_DECL_OVERRIDE;

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
};

typedef QList<TEnemy*> TEnemyList;

#endif // TENEMY_H
