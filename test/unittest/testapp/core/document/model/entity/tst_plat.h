#ifndef TESTPLAT_H
#define TESTPLAT_H

#include <QObject>

class TestPlat : public QObject
{
    Q_OBJECT

public:
    explicit TestPlat(QObject *parent = 0);

private Q_SLOTS:
    
};

#endif // TESTPLAT_H