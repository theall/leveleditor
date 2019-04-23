#ifndef TAREA_H
#define TAREA_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TArea : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TArea(QObject *parent = nullptr);

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

typedef QList<TArea*> TAreaList;

#endif // TAREA_H
