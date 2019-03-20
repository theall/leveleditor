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
    TLayer(QObject *parent=nullptr, const QString &name=QString());
    ~TLayer();

    QString name() const;
    void setName(const QString &name);

    TTileList tileList() const;

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
