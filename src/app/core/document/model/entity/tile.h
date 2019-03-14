#ifndef TTILE_H
#define TTILE_H

#include <QList>
#include <QPainter>

#include "../../base/io.h"
#include "../../base/propertyobject.h"

class TDocument;
class TTile : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    TTile(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

    void render(QPainter *painter, const QRectF &rect);

private:
    QRectF mRect;
    QPixmap mPixmap;
    TDocument *mDocument;
    void initPropertySheet();
};

typedef QList<TTile*> TTileList;

#endif // TTILE_H
