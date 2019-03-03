#ifndef TPLAT_H
#define TPLAT_H

#include <QList>

#include "point.h"
#include "../../base/io.h"
#include "../../base/propertyobject.h"
#include "../../base/pixmap.h"

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
    void initPropertySheet();
};
typedef QList<TPlat*> TPlatsList;

#endif // TPLAT_H
