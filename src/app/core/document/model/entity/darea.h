#ifndef TDAREA_H
#define TDAREA_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TDArea : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TDArea(QObject *parent = nullptr);
    TDArea(const QRect &rect, QObject *parent = Q_NULLPTR);

private:
    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
};

typedef QList<TDArea*> TDAreaList;

#endif // TDAREA_H
