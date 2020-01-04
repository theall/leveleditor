#ifndef TWALL_H
#define TWALL_H

#include <QList>

#include "rectobject.h"

class TWall : public TRectObject
{
    Q_OBJECT

public:
    explicit TWall(QObject *parent = nullptr);
    TWall(const QRect &rect, QObject *parent = Q_NULLPTR);

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

    // TObject interface
public:
    QByteArray toByteArray(TObject *object) const;
    void loadFromByteArray(const QByteArray &byteArray);
};

typedef QList<TWall*> TWallList;

#endif // TWALL_H
