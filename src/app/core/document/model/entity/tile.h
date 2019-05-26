#ifndef TTILE_H
#define TTILE_H

#include <QList>
#include <QPainter>

#include "object.h"
#include "../../base/io.h"

class TTileId;
class TPixmap;
class TDocument;

class TTileMoveModel : QObject
{
public:
    enum Type {
        Recycle,
        Random,
        Follow
    };

    TTileMoveModel(QObject *parent = nullptr);

    Type type() const;
    void setType(const Type &type);

private:
    Type mType;
};

class TStartPoint : public TObject
{
    Q_OBJECT

public:
    explicit TStartPoint(QObject *parent = nullptr);
    ~TStartPoint();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;
};

class TDoor : public TObject
{
    Q_OBJECT

public:
    enum Dir {
        Horizontal,
        Vertical,
        None,
    };
    enum Edge {
        Left = 0x1,
        Right = 0x2,
        LeftRight = Left|Right,
    };
    enum Type {
        Recycle,
        Random,
        Follow
    };
    TDoor(QObject *parent = nullptr);
    Dir dir() const;
    void setDir(const Dir &dir);

    void move(qreal offset, const Edge &edge);
    void slide(const QPointF &offset);

    Type type() const;
    void setType(const Type &type);

    void setPos(const QPointF &pos);
    TStartPoint *startPoint() const;

    void setStartPos(const QPointF &pos);

private:
    Dir mDir;
    Type mType;
    TStartPoint *mStartPoint;

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;
};

class TTile : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TTile(QObject *parent = nullptr);

    QPixmap pixmap() const;
    TPixmap *primitive() const;
    TDoor *door() const;
    bool hasMoveModel() const;

    TTile *target() const;
    void setTarget(TTile *target);
    int targetNumber() const;

    TTileId *tileId() const;
    void setTileId(TTileId *tileId);

private slots:
    void slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue);

private:
    TPixmap *mPixmap;
    TDocument *mDocument;
    TDoor *mDoor;
    TTile *mTarget;
    TTileId *mTileId;
    bool mHasMoveModel;
    int mTargetNumber;

    void setUp();
    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
};

typedef QList<TTile*> TTileList;

#endif // TTILE_H
