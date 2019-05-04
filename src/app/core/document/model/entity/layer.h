#ifndef DOCUMENT_LAYER_H
#define DOCUMENT_LAYER_H

#include <QString>

#include "../../base/io.h"
#include "../../property/propertyobject.h"
#include "tile.h"

class TDocument;
class TLayer : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    enum Type {
        Background,
        Foreground
    };

    TLayer(QObject *parent=nullptr, const QString &name=QString());
    ~TLayer();

    QString name() const;
    void setName(const QString &name);

    TTileList tileList() const;
    Type type() const;
    void setType(const Type &type);

    int tileSize() const;

private:
    Type mType;
    QString mName;
    TDocument *mDocument;
    TTileList mTileList;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
};
typedef QList<TLayer*> TLayerList;

#endif // DOCUMENT_LAYER_H
