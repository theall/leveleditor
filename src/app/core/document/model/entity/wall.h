#ifndef TWALL_H
#define TWALL_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TWall : public TObject, TIO
{
    Q_OBJECT

public:
    TWall(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();
};

typedef QList<TWall*> TWallList;

#endif // TWALL_H
