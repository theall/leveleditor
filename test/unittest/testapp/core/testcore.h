#ifndef TESTCORE_H
#define TESTCORE_H

#include <QObject>

class TestCore : public QObject
{
    Q_OBJECT
public:
    explicit TestCore(QObject *parent = 0);

signals:

public slots:
    void testInit();
};

#endif // TESTCORE_H
