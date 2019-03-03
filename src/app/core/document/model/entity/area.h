#ifndef TAREA_H
#define TAREA_H

#include <QList>

#include "../../base/io.h"
#include "../../base/propertyobject.h"

class TArea : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    TArea(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();
};

typedef QList<TArea*> TAreasList;

#endif // TAREA_H
