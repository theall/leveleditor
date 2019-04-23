#ifndef TPLAT_H
#define TPLAT_H

#include <QList>
#include <QPixmap>

#include "object.h"
#include "../../base/io.h"

class TDocument;
class TPlat : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TPlat(QObject *parent = nullptr);

private:
    TDocument *mDocument;
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
};
typedef QList<TPlat*> TPlatList;

#endif // TPLAT_H
