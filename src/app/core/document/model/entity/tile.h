#ifndef TTILE_H
#define TTILE_H

#include <QList>
#include <QPainter>

#include "object.h"
#include "../../base/io.h"

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
    TStartPoint(QObject *parent = nullptr);

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

    TDoor(QObject *parent = nullptr);
    Dir dir() const;
    void setDir(const Dir &dir);

    void move(qreal offset, const Edge &edge);
    void slide(const QPointF &offset);

private:
    Dir mDir;

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;
};

class TTile : public TObject, TIO
{
    Q_OBJECT

public:
    TTile(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

    QPixmap pixmap() const;
    TPixmap *primitive() const;
    TStartPoint *startPoint() const;
    TDoor *door() const;
    bool hasMoveModel() const;

private slots:
    void slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &oldValue);

private:
    TPixmap *mPixmap;
    TDocument *mDocument;
    TStartPoint *mStartPoint;
    TDoor *mDoor;
    bool mHasMoveModel;

    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;
};

typedef QList<TTile*> TTileList;

#endif // TTILE_H
