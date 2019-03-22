#ifndef TTILE_H
#define TTILE_H

#include <QList>
#include <QPainter>

#include "object.h"
#include "../../base/io.h"

class TPixmap;
class TDocument;
class TTile : public TObject, TIO
{
    Q_OBJECT

public:
    TTile(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

    QPixmap pixmap() const;
    TPixmap *primitive() const;

private:
    TPixmap *mPixmap;
    TDocument *mDocument;
    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;
};

typedef QList<TTile*> TTileList;

#endif // TTILE_H
