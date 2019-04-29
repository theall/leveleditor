#ifndef TANIMATIONFRAME_H
#define TANIMATIONFRAME_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TFrame : public TObject, TIO
{
    Q_OBJECT

public:
    explicit TFrame(QObject *parent = nullptr);
    ~TFrame();

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

typedef QList<TFrame*> TFrameList;

#endif // TANIMATIONFRAME_H
