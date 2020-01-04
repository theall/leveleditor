#ifndef TAREA_H
#define TAREA_H

#include <QList>

#include "areaplat.h"

class TArea : public TAreaPlat
{
    Q_OBJECT

public:
    explicit TArea(QObject *parent = Q_NULLPTR);
    TArea(const QRect &rect, QObject *parent = Q_NULLPTR);

    void setPlatNameList(const QStringList &platNames);

protected:
    virtual void initPropertySheet() override;

private slots:
    void slotBindPlatChanged(TPlat *newPlat, int newIndex, TPlat *oldPlat, int oldIndex);

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

typedef QList<TArea*> TAreaList;

#endif // TAREA_H
