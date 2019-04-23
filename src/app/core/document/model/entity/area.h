#ifndef TAREA_H
#define TAREA_H

#include <QList>

#include "object.h"
#include "../../base/io.h"

class TArea : public TObject, TIO
{
    Q_OBJECT

public:
    TArea(QObject *parent = nullptr);

    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

private:
    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;
    QRectF rect() const Q_DECL_OVERRIDE;
    QPointF pos() const Q_DECL_OVERRIDE;
    void setPos(const QPointF &pos) Q_DECL_OVERRIDE;
    QSize size() const Q_DECL_OVERRIDE;
    void setSize(const QSize &size) Q_DECL_OVERRIDE;
    void setRect(const QRectF &rect) Q_DECL_OVERRIDE;
    void move(const QPointF &offset) Q_DECL_OVERRIDE;
};

typedef QList<TArea*> TAreaList;

#endif // TAREA_H
