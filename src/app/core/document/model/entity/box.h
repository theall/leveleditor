#ifndef TBOX_H
#define TBOX_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TBox : public TObject, TIO
{
    Q_OBJECT

public:
    TBox(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
};

typedef QList<TBox*> TBoxList;

#endif // TBOX_H
