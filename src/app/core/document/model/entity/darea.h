#ifndef TDAREA_H
#define TDAREA_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TDArea : public TObject, TIO
{
    Q_OBJECT

public:
    TDArea(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();
};

typedef QList<TDArea*> TDAreaList;

#endif // TDAREA_H
