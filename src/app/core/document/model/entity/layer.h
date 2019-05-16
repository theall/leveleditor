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

    void insertTile(TTile *tile, int index = -1);
    void insertTile(const TTileList &tileList, const QList<int> &indexList = QList<int>());

    int removeTile(int index);
    int removeTile(TTile *tile);
    QList<int> removeTile(const QList<int> &indexList);
    QList<int> removeTile(const TTileList &tileList);

signals:
    void tileInserted(const TTileList &tileList, const QList<int> &indexList);
    void tileRemoved(const TTileList &tileList, const QList<int> &indexList);

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
