#ifndef TBOX_H
#define TBOX_H

#include <QList>

#include "../../base/io.h"
#include "../../base/propertyobject.h"

class TBox : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    TBox(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();
};

typedef QList<TBox*> TBoxList;

#endif // TBOX_H
