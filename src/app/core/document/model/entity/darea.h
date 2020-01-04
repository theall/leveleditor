#ifndef TDAREA_H
#define TDAREA_H

#include <QList>

#include "areaplat.h"

class TDArea : public TAreaPlat
{
    Q_OBJECT

public:
    explicit TDArea(QObject *parent = nullptr);
    TDArea(const QRect &rect, QObject *parent = Q_NULLPTR);

private slots:
    void slotAiEscapeModePropertyChanged(const QVariant &oldValue, const QVariant &newValue);

private:
    TPropertyItem *mEscapePropertyItem;
    TPropertyItem *mTargetPropertyItem;

    void initPropertySheet();

    // TObject interface
public:
    QString typeString() const Q_DECL_OVERRIDE;
    bool isCongener(TObject *object) const Q_DECL_OVERRIDE;

    // TIO interface
public:
    void saveToStream(QDataStream &stream) const Q_DECL_OVERRIDE;
    void readFromStream(QDataStream &stream) Q_DECL_OVERRIDE;

    // TObject interface
public:
    QByteArray toByteArray(TObject *object) const;
    void loadFromByteArray(const QByteArray &byteArray);
    void move(const QPointF &offset);
};

typedef QList<TDArea*> TDAreaList;

#endif // TDAREA_H
