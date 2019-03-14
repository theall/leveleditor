#ifndef DOCUMENT_LAYER_H
#define DOCUMENT_LAYER_H

#include <QString>

#include "../../base/io.h"
#include "../../base/propertyobject.h"
#include "tile.h"

class TDocument;
class TLayer : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    TLayer(const QString &name, QObject *parent=nullptr);
    ~TLayer();

    QString name() const;
    void setName(const QString &name);

    void render(QPainter *painter, const QRectF &rect);

private:
    QString mName;
    TDocument *mDocument;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    TTileList mTileList;
};


#endif // DOCUMENT_LAYER_H
