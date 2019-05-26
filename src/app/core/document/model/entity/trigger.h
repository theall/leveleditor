#ifndef TTRIGGER_H
#define TTRIGGER_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TTrigger : public TObject, TIO
{
    Q_OBJECT

public:
    TTrigger(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const;
    bool isCongener(TObject *object) const;
};

typedef QList<TTrigger*> TTriggerList;

#endif // TTRIGGER_H
