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

typedef QList<TWall*> TWallList;

#endif // TWALL_H
