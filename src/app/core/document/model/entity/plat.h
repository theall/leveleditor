#ifndef TPLAT_H
#define TPLAT_H

#include <QList>
#include <QPixmap>

#include "object.h"
#include "../../base/io.h"

class TDocument;
class TPlat : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    TPlat(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    TDocument *mDocument;
    QPixmap mPixmap;
    QList<QPoint> mPointList;
    void initPropertySheet();
};
typedef QList<TPlat*> TPlatList;

#endif // TPLAT_H
