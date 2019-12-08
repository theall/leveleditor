#ifndef TAREA_H
#define TAREA_H

#include <QList>

#include "rectobject.h"

class TArea : public TRectObject
{
    Q_OBJECT

public:
    explicit TArea(QObject *parent = Q_NULLPTR);
    TArea(const QRect &rect, QObject *parent = Q_NULLPTR);

    void setPlatNameList(const QStringList &platNames);

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
