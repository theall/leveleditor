#ifndef TTRIGGER_H
#define TTRIGGER_H

#include <QList>

#include "rectobject.h"

class TTriggerId;
class TTrigger : public TRectObject
{
    Q_OBJECT

public:
    TTrigger(QObject *parent = nullptr);

    TTriggerId *triggerId() const;
    void setTriggerId(TTriggerId *triggerId);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

    QPointF getImageOffset() const;

private:
    TTriggerId *mTriggerId;
    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const;
    bool isCongener(TObject *object) const;
};

typedef QList<TTrigger*> TTriggerList;

#endif // TTRIGGER_H
