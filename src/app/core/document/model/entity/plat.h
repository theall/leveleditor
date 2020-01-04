#ifndef TPLAT_H
#define TPLAT_H

#include <QList>
#include <QPixmap>

#include "rectobject.h"

class TPlat : public TRectObject
{
    Q_OBJECT

public:
    explicit TPlat(QObject *parent = nullptr);
    TPlat(const QRect &rect, QObject *parent = Q_NULLPTR);

private:
    QPixmap mPixmap;
    QList<QPoint> mPointList;

	void initPropertySheet();

    // TObject interface
public:
    QString typeString() const;
    bool isCongener(TObject *object) const;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

    // TObject interface
public:
    QByteArray toByteArray(TObject *object) const;
    void loadFromByteArray(const QByteArray &byteArray);
};
typedef QList<TPlat*> TPlatList;

#endif // TPLAT_H
