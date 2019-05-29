#ifndef TESTMAP_H
#define TESTMAP_H

#include <QObject>

class TestMap : public QObject
{
    Q_OBJECT

public:
    explicit TestMap(QObject *parent = 0);

private Q_SLOTS:
    void testNewMap();
    void testOpenMap();
    void testSaveMap();
};

#endif // TESTMAP_H
