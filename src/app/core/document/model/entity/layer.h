#ifndef DOCUMENT_LAYER_H
#define DOCUMENT_LAYER_H

#include <QPoint>

#include "../../base/io.h"
#include "../../base/propertyobject.h"

class TDocument;

class TLayer : public TPropertyObject, TIO
{
    Q_OBJECT

public:
    TLayer(const QString &name, QObject *parent=nullptr);
    ~TLayer();

    void readFromStream(const QDataStream &stream, void *context=nullptr);

    QString name() const;
    void setName(const QString &name);

    QPointF offset() const;
    void setOffset(const QPointF &offset);

    TPropertySheet *propertySheet() const;

signals:

private slots:
    void slotPropertyItemValueChanged(TPropertyItem *item, const QVariant &value);

private:
    QString mName;
    QPoint mOffset;
    TDocument *mDocument;

    void initPropertySheet();

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;
};


#endif // DOCUMENT_LAYER_H
