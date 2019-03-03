#ifndef TDAREA_H
#define TDAREA_H

#include <QList>

#include "../../base/io.h"
#include "../../base/propertyobject.h"

class TDArea : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    TDArea(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();
};

typedef QList<TDArea*> TDAreasList;

#endif // TDAREA_H
