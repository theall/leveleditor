#ifndef TTRIGGER_H
#define TTRIGGER_H

#include <QList>

#include "../../base/io.h"
#include "../../base/propertyobject.h"

class TTrigger : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    TTrigger(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();
};

typedef QList<TTrigger*> TTriggerList;

#endif // TTRIGGER_H
